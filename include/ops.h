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
    fprintf(stderr, "Error: invalid opcode:  0x%02x\n", op);
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
        .name = "nop",
        .func = func_nop,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x01,
        .name = "ld BC,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0x02,
        .name = "ld (BC),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x03,
        .name = "inc BC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x04,
        .name = "inc B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x05,
        .name = "dec B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x06,
        .name = "ld B,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x07,
        .name = "rlca",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x08,
        .name = "ld (u16),SP",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 5
    },
    {
        .op = 0x09,
        .name = "add HL,BC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x0a,
        .name = "ld A,(BC)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x0b,
        .name = "dec BC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x0c,
        .name = "inc C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x0d,
        .name = "dec C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x0e,
        .name = "ld C,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x0f,
        .name = "rrca",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x10,
        .name = "stop",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 1
    },
    {
        .op = 0x11,
        .name = "ld DE,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0x12,
        .name = "ld (DE),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x13,
        .name = "inc DE",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x14,
        .name = "inc D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x15,
        .name = "dec D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x16,
        .name = "ld D,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x17,
        .name = "rla",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x18,
        .name = "jr i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 3
    },
    {
        .op = 0x19,
        .name = "add HL,DE",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x1a,
        .name = "ld A,(DE)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x1b,
        .name = "dec DE",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x1c,
        .name = "inc E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x1d,
        .name = "dec E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x1e,
        .name = "ld E,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x1f,
        .name = "rra",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x20,
        .name = "jr NZ,i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x21,
        .name = "ld HL,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0x22,
        .name = "ld (HL+),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x23,
        .name = "inc HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x24,
        .name = "inc H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x25,
        .name = "dec H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x26,
        .name = "ld H,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x27,
        .name = "daa",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x28,
        .name = "jr Z,i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x29,
        .name = "add HL,HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x2a,
        .name = "ld A,(HL+)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x2b,
        .name = "dec HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x2c,
        .name = "inc L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x2d,
        .name = "dec L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x2e,
        .name = "ld L,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x2f,
        .name = "cpl",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x30,
        .name = "jr NC,i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x31,
        .name = "ld SP,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0x32,
        .name = "ld (HL-),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x33,
        .name = "inc SP",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x34,
        .name = "inc (HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0x35,
        .name = "dec (HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0x36,
        .name = "ld (HL),u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 3
    },
    {
        .op = 0x37,
        .name = "scf",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x38,
        .name = "jr C,i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x39,
        .name = "add HL,SP",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x3a,
        .name = "ld A,(HL-)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x3b,
        .name = "dec SP",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x3c,
        .name = "inc A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x3d,
        .name = "dec A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x3e,
        .name = "ld A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0x3f,
        .name = "ccf",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x40,
        .name = "ld B,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x41,
        .name = "ld B,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x42,
        .name = "ld B,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x43,
        .name = "ld B,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x44,
        .name = "ld B,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x45,
        .name = "ld B,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x46,
        .name = "ld B,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x47,
        .name = "ld B,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x48,
        .name = "ld C,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x49,
        .name = "ld C,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x4a,
        .name = "ld C,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x4b,
        .name = "ld C,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x4c,
        .name = "ld C,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x4d,
        .name = "ld C,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x4e,
        .name = "ld C,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x4f,
        .name = "ld C,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x50,
        .name = "ld D,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x51,
        .name = "ld D,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x52,
        .name = "ld D,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x53,
        .name = "ld D,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x54,
        .name = "ld D,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x55,
        .name = "ld D,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x56,
        .name = "ld D,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x57,
        .name = "ld D,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x58,
        .name = "ld E,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x59,
        .name = "ld E,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x5a,
        .name = "ld E,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x5b,
        .name = "ld E,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x5c,
        .name = "ld E,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x5d,
        .name = "ld E,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x5e,
        .name = "ld E,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x5f,
        .name = "ld E,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x60,
        .name = "ld H,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x61,
        .name = "ld H,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x62,
        .name = "ld H,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x63,
        .name = "ld H,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x64,
        .name = "ld H,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x65,
        .name = "ld H,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x66,
        .name = "ld H,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x67,
        .name = "ld H,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x68,
        .name = "ld L,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x69,
        .name = "ld L,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x6a,
        .name = "ld L,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x6b,
        .name = "ld L,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x6c,
        .name = "ld L,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x6d,
        .name = "ld L,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x6e,
        .name = "ld L,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x6f,
        .name = "ld L,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x70,
        .name = "ld (HL),B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x71,
        .name = "ld (HL),C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x72,
        .name = "ld (HL),D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x73,
        .name = "ld (HL),E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x74,
        .name = "ld (HL),H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x75,
        .name = "ld (HL),L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x76,
        .name = "halt",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x77,
        .name = "ld (HL),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x78,
        .name = "ld A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x79,
        .name = "ld A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x7a,
        .name = "ld A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x7b,
        .name = "ld A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x7c,
        .name = "ld A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x7d,
        .name = "ld A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x7e,
        .name = "ld A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x7f,
        .name = "ld A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x80,
        .name = "add A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x81,
        .name = "add A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x82,
        .name = "add A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x83,
        .name = "add A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x84,
        .name = "add A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x85,
        .name = "add A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x86,
        .name = "add A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x87,
        .name = "add A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x88,
        .name = "adc A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x89,
        .name = "adc A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x8a,
        .name = "adc A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x8b,
        .name = "adc A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x8c,
        .name = "adc A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x8d,
        .name = "adc A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x8e,
        .name = "adc A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x8f,
        .name = "adc A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x90,
        .name = "sub A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x91,
        .name = "sub A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x92,
        .name = "sub A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x93,
        .name = "sub A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x94,
        .name = "sub A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x95,
        .name = "sub A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x96,
        .name = "sub A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x97,
        .name = "sub A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x98,
        .name = "sbc A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x99,
        .name = "sbc A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x9a,
        .name = "sbc A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x9b,
        .name = "sbc A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x9c,
        .name = "sbc A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x9d,
        .name = "sbc A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0x9e,
        .name = "sbc A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0x9f,
        .name = "sbc A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa0,
        .name = "and A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa1,
        .name = "and A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa2,
        .name = "and A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa3,
        .name = "and A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa4,
        .name = "and A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa5,
        .name = "and A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa6,
        .name = "and A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xa7,
        .name = "and A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa8,
        .name = "xor A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xa9,
        .name = "xor A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xaa,
        .name = "xor A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xab,
        .name = "xor A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xac,
        .name = "xor A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xad,
        .name = "xor A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xae,
        .name = "xor A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xaf,
        .name = "xor A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb0,
        .name = "or A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb1,
        .name = "or A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb2,
        .name = "or A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb3,
        .name = "or A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb4,
        .name = "or A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb5,
        .name = "or A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb6,
        .name = "or A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xb7,
        .name = "or A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb8,
        .name = "cp A,B",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xb9,
        .name = "cp A,C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xba,
        .name = "cp A,D",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xbb,
        .name = "cp A,E",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xbc,
        .name = "cp A,H",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xbd,
        .name = "cp A,L",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xbe,
        .name = "cp A,(HL)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xbf,
        .name = "cp A,A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xc0,
        .name = "ret NZ",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xc1,
        .name = "pop BC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0xc2,
        .name = "jp NZ,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xc3,
        .name = "jp u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 4
    },
    {
        .op = 0xc4,
        .name = "call NZ,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xc5,
        .name = "push BC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xc6,
        .name = "add A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xc7,
        .name = "rst 00h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xc8,
        .name = "ret Z",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xc9,
        .name = "ret",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xca,
        .name = "jp Z,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xcb,
        .name = "prefix CB",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xcc,
        .name = "call Z,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xcd,
        .name = "call u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 6
    },
    {
        .op = 0xce,
        .name = "adc A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xcf,
        .name = "rst 08h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xd0,
        .name = "ret NC",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xd1,
        .name = "pop DE",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0xd2,
        .name = "jp NC,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xd3,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xd4,
        .name = "call NC,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xd5,
        .name = "push DE",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xd6,
        .name = "sub A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xd7,
        .name = "rst 10h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xd8,
        .name = "ret C",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xd9,
        .name = "reti",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xda,
        .name = "jp C,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xdb,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xdc,
        .name = "call C,u16",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 3
    },
    {
        .op = 0xdd,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xde,
        .name = "sbc A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xdf,
        .name = "rst 18h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xe0,
        .name = "ld (FF00+u8),A",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 3
    },
    {
        .op = 0xe1,
        .name = "pop HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0xe2,
        .name = "ld (FF00+C),A",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xe3,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xe4,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xe5,
        .name = "push HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xe6,
        .name = "and A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xe7,
        .name = "rst 20h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xe8,
        .name = "add SP,i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 4
    },
    {
        .op = 0xe9,
        .name = "jp HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xea,
        .name = "ld (u16),A",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 4
    },
    {
        .op = 0xeb,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xec,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xed,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xee,
        .name = "xor A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xef,
        .name = "rst 28h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xf0,
        .name = "ld A,(FF00+u8)",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 3
    },
    {
        .op = 0xf1,
        .name = "pop AF",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 3
    },
    {
        .op = 0xf2,
        .name = "ld A,(FF00+C)",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xf3,
        .name = "di",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xf4,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xf5,
        .name = "push AF",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xf6,
        .name = "or A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xf7,
        .name = "rst 30h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    },
    {
        .op = 0xf8,
        .name = "ld HL,SP+i8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 3
    },
    {
        .op = 0xf9,
        .name = "ld SP,HL",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 2
    },
    {
        .op = 0xfa,
        .name = "ld A,(u16)",
        .func = func_not_implemented,
        .size = 3,
        .cycles = 4
    },
    {
        .op = 0xfb,
        .name = "ei",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 1
    },
    {
        .op = 0xfc,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xfd,
        .name = "invalid",
        .func = func_invalid,
        .size = 1,
        .cycles = 0
    },
    {
        .op = 0xfe,
        .name = "cp A,u8",
        .func = func_not_implemented,
        .size = 2,
        .cycles = 2
    },
    {
        .op = 0xff,
        .name = "rst 38h",
        .func = func_not_implemented,
        .size = 1,
        .cycles = 4
    }
};

#endif /* !BOI_OPS_H */
