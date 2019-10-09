#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "gb.h"

/* Misc macros */
#define ROM_NAME_SIZE 16
#define NINTENDO_LOGO_SIZE 0x30

/* Offsets for fields in GameBoy ROM header */
#define LOGO_OFF     0x104
#define NAME_OFF     0x134
#define TYPE_OFF     0x147
#define ROM_SIZE_OFF 0x148
#define RAM_SIZE_OFF 0x149
#define REGION_OFF   0x14a
#define VERSION_OFF  0x14c
#define CHECKSUM_OFF 0x14d

/* Boundaries of the area involved in the checksum computing */
#define CHECKSUM_START 0x134
#define CHECKSUM_STOP  0x14c

/* Number of supported cartridge types (MBC1, MMM01, plain ROM...) */
#define CARTRIDGE_TYPE_COUNT 28

static const uint8_t nintendo_logo[NINTENDO_LOGO_SIZE] = {
    0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,
    0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
    0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99,
    0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
    0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e
};


static const struct cartridge_s rom_cartridges[CARTRIDGE_TYPE_COUNT] = {
    {
        .id = 0x00,
        .type = ROM,
        .name = "ROM ONLY"
    },
    {
        .id = 0x1,
        .type = MBC1,
        .name = "MBC1"
    },
    {
        .id = 0x2,
        .type = MBC1,
        .name = "MBC1+RAM"
    },
    {
        .id = 0x3,
        .type = MBC1,
        .name = "MBC1+RAM+BATTERY"
    },
    {
        .id = 0x5,
        .type = MBC2,
        .name = "MBC2"
    },
    {
        .id = 0x6,
        .type = MBC2,
        .name = "MBC2+BATTERY"
    },
    {
        .id = 0x8,
        .type = ROM,
        .name = "ROM+RAM"
    },
    {
        .id = 0x9,
        .type = ROM,
        .name = "ROM+RAM+BATTERY"
    },
    {
        .id = 0xb,
        .type = MMM01,
        .name = "MMM01"
    },
    {
        .id = 0xc,
        .type = MMM01,
        .name = "MMM01+RAM"
    },
    {
        .id = 0xd,
        .type = MMM01,
        .name = "MMM01+RAM+BATTERY"
    },
    {
        .id = 0xf,
        .type = MBC3,
        .name = "MBC3+TIMER+BATTERY"
    },
    {
        .id = 0x10,
        .type = MBC3,
        .name = "MBC3+TIMER+RAM+BATTERY"
    },
    {
        .id = 0x11,
        .type = MBC3,
        .name = "MBC3"
    },
    {
        .id = 0x12,
        .type = MBC3,
        .name = "MBC3+RAM"
    },
    {
        .id = 0x13,
        .type = MBC3,
        .name = "MBC3+RAM+BATTERY"
    },
    {
        .id = 0x19,
        .type = MBC5,
        .name = "MBC5"
    },
    {
        .id = 0x1a,
        .type = MBC5,
        .name = "MBC5+RAM"
    },
    {
        .id = 0x1b,
        .type = MBC5,
        .name = "MBC5+RAM+BATTERY"
    },
    {
        .id = 0x1c,
        .type = MBC5,
        .name = "MBC5+RUMBLE"
    },
    {
        .id = 0x1d,
        .type = MBC5,
        .name = "MBC5+RUMBLE+RAM"
    },
    {
        .id = 0x1e,
        .type = MBC5,
        .name = "MBC5+RUMBLE+RAM+BATTERY"
    }
};

/* Parse GameBoy header */
static void rom_init(struct gb_s *gb)
{
    struct cartridge_s rom_cartridge;
    char rom_name[ROM_NAME_SIZE + 1];
    uint8_t rom_type;
    uint8_t rom_checksum = 0;
    uint16_t index;

    /* Check Nintendo logo */
    if (memcmp(gb->rom.raw + LOGO_OFF, nintendo_logo, NINTENDO_LOGO_SIZE)) {
        fprintf(stderr, "Invalid Nintendo logo in ROM...");
        exit(EXIT_FAILURE);
    }
    printf("Found valid Nintendo logo...\n");

    /* Dump name */
    memcpy(rom_name, gb->rom.raw + NAME_OFF, ROM_NAME_SIZE);
    rom_name[ROM_NAME_SIZE] = '\0';
    printf("ROM name: %s\n", rom_name);

    /* Dump cartridge type */
    rom_type = gb->rom.raw[TYPE_OFF];
    for (index = 0; index < CARTRIDGE_TYPE_COUNT; ++index) {
        if (rom_cartridges[index].id == rom_type) {
            rom_cartridge = rom_cartridges[index];
            break;
        }
    }
    if (index == CARTRIDGE_TYPE_COUNT){
        fprintf(stderr, "Invalid or unsupported cartridge type: %x", rom_type);
        exit(EXIT_FAILURE);
    }
    printf("Cartridge type 0x%x: %s\n", rom_cartridge.id, rom_cartridge.name);
    gb->rom.type = rom_cartridge.type;

    /*
     * TODO: dump ROM and RAM sizes
     */

    /* Dump ROM region */
    if (!gb->rom.raw[REGION_OFF])
        printf("Region: Japan\n");
    else
        printf("Region: Non-Japan\n");

    /* Dump ROM version */
    printf("Version: 0x%02x\n", gb->rom.raw[VERSION_OFF]);

    /* Verify header checksum */
    for (index = CHECKSUM_START; index <= CHECKSUM_STOP; ++index)
        rom_checksum -= gb->rom.raw[index] + 1;
    if (rom_checksum != gb->rom.raw[CHECKSUM_OFF]) {
        fprintf(stderr, "Invalid checksum: found 0x%02x and expected 0x%02x\n",
                rom_checksum, gb->rom.raw[CHECKSUM_OFF]);
        exit(EXIT_FAILURE);
    } else {
        printf("A valid header checksum was found: 0x%02x...\n", rom_checksum);
    }
}

/* Map GameBoy header and call parsing function */
void rom_load(struct gb_s *gb, const char *const filename)
{
    int fd;
    struct stat st;

    if ((fd = open(filename, O_RDONLY)) == -1) {
        fprintf(stderr, "Error while opening ROM %s: %s\n", filename,
                strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (fstat(fd, &st) == -1) {
        fprintf(stderr, "Error while reading info from ROM: %s\n",
                strerror(errno));
        exit(EXIT_FAILURE);
    }
    if ((gb->rom.raw = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
            == NULL) {
        fprintf(stderr, "Error while mapping ROM: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    rom_init(gb);
}
