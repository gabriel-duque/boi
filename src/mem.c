#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gb.h"

#define MEM_SIZE 0x10000

/* Map and initialize the systems memory */
void mem_init(struct gb_s *gb)
{
    if ((gb->mem.raw = calloc(1, MEM_SIZE)) == NULL) {
        fprintf(stderr, "Error while calling calloc: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Map cartridge bytes into memory from 0x0000 to 0x7fff */
    memcpy(gb->mem.raw, gb->rom.raw, 0x8000);

    /*
     * Initialize a bunch of values that are needed:
     * See: http://bgb.bircd.org/pandocs.htm#powerupsequence
     */

    gb->mem.raw[0xff05] = 0x00;
    gb->mem.raw[0xff06] = 0x00;
    gb->mem.raw[0xff07] = 0x00;
    gb->mem.raw[0xff10] = 0x80;
    gb->mem.raw[0xff11] = 0xbf;
    gb->mem.raw[0xff12] = 0xf3;
    gb->mem.raw[0xff14] = 0xbf;
    gb->mem.raw[0xff16] = 0x3f;
    gb->mem.raw[0xff17] = 0x00;
    gb->mem.raw[0xff19] = 0xbf;
    gb->mem.raw[0xff1a] = 0x7f;
    gb->mem.raw[0xff1b] = 0xff;
    gb->mem.raw[0xff1c] = 0x9f;
    gb->mem.raw[0xff1e] = 0xbf;
    gb->mem.raw[0xff20] = 0xff;
    gb->mem.raw[0xff21] = 0x00;
    gb->mem.raw[0xff22] = 0x00;
    gb->mem.raw[0xff23] = 0xbf;
    gb->mem.raw[0xff24] = 0x77;
    gb->mem.raw[0xff25] = 0xf3;
    gb->mem.raw[0xff26] = 0xf1;
    gb->mem.raw[0xff40] = 0x91;
    gb->mem.raw[0xff42] = 0x00;
    gb->mem.raw[0xff43] = 0x00;
    gb->mem.raw[0xff45] = 0x00;
    gb->mem.raw[0xff47] = 0xfc;
    gb->mem.raw[0xff48] = 0xff;
    gb->mem.raw[0xff49] = 0xff;
    gb->mem.raw[0xff4a] = 0x00;
    gb->mem.raw[0xff4b] = 0x00;
    gb->mem.raw[0xffff] = 0x00;

    gb->mem.dma_pending = 0;

    printf("Memory successfully initialized...\n");

    return;
}

uint8_t mem_read_byte(struct gb_s *gb, uint16_t off)
{
    uint32_t elapsed;
    if (gb->mem.dma_pending && off < 0xff80) {
        elapsed = gb->cpu.cycles - gb->mem.dma_pending;
        if (elapsed >= 160)
            gb->mem.dma_pending = 0;
        else
            return gb->mem.raw[0xfe00 + elapsed];
    }

    if (off < 0xff00)
        return gb->mem.raw[off];

    switch (off) {
        case 0xff00:
        case 0xff04:
        case 0xff05:
        case 0xff06:
        case 0xff07:
        case 0xff0f:
        case 0xff41:
        case 0xff44:
        case 0xff4d:
        case 0xffff:
            fprintf(stderr, "Bad write target address: 0x%02x...\n", off);
            exit(EXIT_FAILURE);
    }

    return gb->mem.raw[off];
}

uint16_t mem_read_word(struct gb_s *gb, uint16_t off)
{
    uint32_t elapsed;
    if (gb->mem.dma_pending && off < 0xff80) {
        elapsed = gb->cpu.cycles - gb->mem.dma_pending;
        if (elapsed >= 160)
            gb->mem.dma_pending = 0;
        else
            return gb->mem.raw[0xfe00 + elapsed];
    }
    return (((uint16_t) gb->mem.raw[off + 1]) << 8) | gb->mem.raw[off];
}

void mem_write_byte(struct gb_s *gb, uint16_t off, uint8_t val)
{
    bool skip = false;

    switch (gb->rom.type) {
        case ROM:
            if (off < 0x8000)
                skip = true;
            break;
        case MBC1:
            break;
        case MBC2:
            break;
        case MBC3:
            break;
        default:
            fprintf(stderr, "%s\n", "Unsupported type of cartridge...");
            exit(EXIT_FAILURE);
            break;
    }

    if (skip)
        return;

    switch (off) {
        case 0xff00:
        case 0xff01:
        case 0xff04:
        case 0xff05:
        case 0xff06:
        case 0xff07:
        case 0xff0f:
        case 0xff40:
        case 0xff41:
        case 0xff42:
        case 0xff43:
        case 0xff45:
        case 0xff46:
        case 0xff47:
        case 0xff48:
        case 0xff49:
        case 0xff4a:
        case 0xff4b:
        case 0xffff:
            fprintf(stderr, "Bad write target address: 0x%02x...\n", off);
            exit(EXIT_FAILURE);
    }

    gb->mem.raw[off] = val;
}

void mem_write_word(struct gb_s *gb, uint16_t off, uint16_t val)
{
    /* TODO: handle MBC and filtering for ro memory parts */
    /* Avoid casting gb->mem + off to a (uint16_t *) */
    gb->mem.raw[off] = val & 0xff;
    gb->mem.raw[off + 1] = val >> 8;
}
