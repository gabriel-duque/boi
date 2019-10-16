#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gb.h"

#define MEM_SIZE 0x10000

/* Map and initialize the systems memory */
void mem_init(struct gb_s *gb)
{
    if ((gb->mem = calloc(1, MEM_SIZE)) == NULL) {
        fprintf(stderr, "Error while calling calloc: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Map cartridge bytes into memory from 0x0000 0x7fff */
    memcpy(gb->mem, gb->rom.raw, 0x8000);

    /*
     * Initialize a bunch of values that are needed:
     * See: http://bgb.bircd.org/pandocs.htm#powerupsequence
     */

    gb->mem[0xff05] = 0x00;
    gb->mem[0xff06] = 0x00;
    gb->mem[0xff07] = 0x00;
    gb->mem[0xff10] = 0x80;
    gb->mem[0xff11] = 0xbf;
    gb->mem[0xff12] = 0xf3;
    gb->mem[0xff14] = 0xbf;
    gb->mem[0xff16] = 0x3f;
    gb->mem[0xff17] = 0x00;
    gb->mem[0xff19] = 0xbf;
    gb->mem[0xff1a] = 0x7f;
    gb->mem[0xff1b] = 0xff;
    gb->mem[0xff1c] = 0x9f;
    gb->mem[0xff1e] = 0xbf;
    gb->mem[0xff20] = 0xff;
    gb->mem[0xff21] = 0x00;
    gb->mem[0xff22] = 0x00;
    gb->mem[0xff23] = 0xbf;
    gb->mem[0xff24] = 0x77;
    gb->mem[0xff25] = 0xf3;
    gb->mem[0xff26] = 0xf1;
    gb->mem[0xff40] = 0x91;
    gb->mem[0xff42] = 0x00;
    gb->mem[0xff43] = 0x00;
    gb->mem[0xff45] = 0x00;
    gb->mem[0xff47] = 0xfc;
    gb->mem[0xff48] = 0xff;
    gb->mem[0xff49] = 0xff;
    gb->mem[0xff4a] = 0x00;
    gb->mem[0xff4b] = 0x00;
    gb->mem[0xffff] = 0x00;

    printf("Memory successfully initialized...\n");

    return;
}

uint8_t  mem_get_byte(struct gb_s *gb, uint16_t off)
{
    return gb->mem[off];
}

uint16_t mem_get_word(struct gb_s *gb, uint16_t off)
{
    /* TODO: check off is not equal to 0xffff (the last byte) */
    return (((uint16_t) gb->mem[off + 1]) << 8) | gb->mem[off];
}

void mem_write_byte(struct gb_s *gb, uint16_t off, uint8_t val)
{
    /* TODO: handle MBC and filtering for ro memory parts */
    gb->mem[off] = val;
}

void mem_write_word(struct gb_s *gb, uint16_t off, uint16_t val)
{
    /* TODO: handle MBC and filtering for ro memory parts */
    /* Avoid casting gb->mem + off to a (uint16_t *) */
    gb->mem[off] = val & 0xff;
    gb->mem[off] = val >> 8;
}
