#ifndef BOI_OPS_H
#define BOI_OPS_H

#include <stdio.h>

#include "gb.h"

#define OPCODE_COUNT    256
#define CB_PREFIX_COUNT 256

static inline bool func_not_implemented(struct gb_s *gb, uint8_t op)
{
    UNUSED(gb);
    UNUSED(op);
    return true;
}

static inline bool func_invalid(struct gb_s *gb, uint8_t op)
{
    UNUSED(gb);
    fprintf(stderr, "%s 0x%02x\n", "Error: invalid opcode:", op);
    return false;
}

static inline bool func_nop(struct gb_s *gb, uint8_t op)
{
    UNUSED(gb);
    UNUSED(op);
    return true;
}

static const struct op_s opcodes[OPCODE_COUNT] = {
    {
        .op = 0x00,
        .name = "NOP",
        .func = func_nop,
        .size = 1
    },
    {
        .op = 0x01,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x02,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x03,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x04,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x05,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x06,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x07,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x08,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x09,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x0f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x10,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x11,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x12,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x13,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x14,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x15,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x16,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x17,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x18,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x19,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x1f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x20,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x21,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x22,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x23,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x24,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x25,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x26,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x27,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x28,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x29,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x2f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x30,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x31,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x32,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x33,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x34,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x35,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x36,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x37,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x38,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x39,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x3f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x40,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x41,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x42,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x43,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x44,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x45,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x46,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x47,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x48,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x49,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x4f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x50,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x51,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x52,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x53,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x54,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x55,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x56,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x57,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x58,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x59,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x5f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x60,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x61,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x62,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x63,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x64,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x65,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x66,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x67,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x68,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x69,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x6f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x70,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x71,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x72,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x73,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x74,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x75,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x76,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x77,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x78,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x79,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x7f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x80,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x81,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x82,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x83,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x84,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x85,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x86,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x87,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x88,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x89,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x8f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x90,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x91,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x92,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x93,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x94,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x95,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x96,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x97,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x98,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x99,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9a,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9b,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9c,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9d,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9e,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0x9f,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa3,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa4,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xa9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xaa,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xab,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xac,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xad,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xae,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xaf,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb3,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb4,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xb9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xba,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xbb,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xbc,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xbd,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xbe,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xbf,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc3,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc4,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xc9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xca,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xcb,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xcc,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xcd,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xce,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xcf,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd3,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xd4,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xd9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xda,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xdb,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xdc,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xdd,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xde,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xdf,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xe0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe3,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xe4,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xe5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xe9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xea,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xeb,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xec,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xed,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xee,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xef,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf0,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf1,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf2,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf3,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf4,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xf5,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf6,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf7,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf8,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xf9,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xfa,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xfb,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xfc,
        .name = "INVALID",
        .func = func_invalid,
        .size = 0
    },
    {
        .op = 0xfd,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xfe,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    },
    {
        .op = 0xff,
        .name = "NOT IMPLEMENTED",
        .func = func_not_implemented,
        .size = 1
    }
};

#endif /* !BOI_OPS_H */
