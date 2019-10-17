#ifndef BOI_OPS_H
#define BOI_OPS_H

#define CB_SINGLE_OP_COUNT 8
#define CB_DOUBLE_OP_COUNT 3

#ifdef _BOI_DEBUG

#include <stdint.h>
#include <stdio.h>

#define OPCODE_COUNT 256

static const char *opcodes[OPCODE_COUNT] = {
    "nop",
    "ld BC, u16",
    "ld (BC), A",
    "inc BC",
    "inc B",
    "dec B",
    "ld B, u8",
    "rlca",
    "ld (u16), SP",
    "add HL, BC",
    "ld A, (BC)",
    "dec BC",
    "inc C",
    "dec C",
    "ld C, u8",
    "rrca",
    "stop",
    "ld DE, u16",
    "ld (DE), A",
    "inc DE",
    "inc D",
    "dec D",
    "ld D, u8",
    "rla",
    "jr i8",
    "add HL, DE",
    "ld A, (DE)",
    "dec DE",
    "inc E",
    "dec E",
    "ld E, u8",
    "rra",
    "jr NZ, i8",
    "ld HL, u16",
    "ld (HL+), A",
    "inc HL",
    "inc H",
    "dec H",
    "ld H, u8",
    "daa",
    "jr Z, i8",
    "add HL, HL",
    "ld A, (HL+)",
    "dec HL",
    "inc L",
    "dec L",
    "ld L, u8",
    "cpl",
    "jr NC, i8",
    "ld SP, u16",
    "ld (HL-), A",
    "inc SP",
    "inc (HL)",
    "dec (HL)",
    "ld (HL), u8",
    "scf",
    "jr C, i8",
    "add HL, SP",
    "ld A, (HL-)",
    "dec SP",
    "inc A",
    "dec A",
    "ld A, u8",
    "ccf",
    "ld B, B",
    "ld B, C",
    "ld B, D",
    "ld B, E",
    "ld B, H",
    "ld B, L",
    "ld B, (HL)",
    "ld B, A",
    "ld C, B",
    "ld C, C",
    "ld C, D",
    "ld C, E",
    "ld C, H",
    "ld C, L",
    "ld C, (HL)",
    "ld C, A",
    "ld D, B",
    "ld D, C",
    "ld D, D",
    "ld D, E",
    "ld D, H",
    "ld D, L",
    "ld D, (HL)",
    "ld D, A",
    "ld E, B",
    "ld E, C",
    "ld E, D",
    "ld E, E",
    "ld E, H",
    "ld E, L",
    "ld E, (HL)",
    "ld E, A",
    "ld H, B",
    "ld H, C",
    "ld H, D",
    "ld H, E",
    "ld H, H",
    "ld H, L",
    "ld H, (HL)",
    "ld H, A",
    "ld L, B",
    "ld L, C",
    "ld L, D",
    "ld L, E",
    "ld L, H",
    "ld L, L",
    "ld L, (HL)",
    "ld L, A",
    "ld (HL), B",
    "ld (HL), C",
    "ld (HL), D",
    "ld (HL), E",
    "ld (HL), H",
    "ld (HL), L",
    "halt",
    "ld (HL), A",
    "ld A, B",
    "ld A, C",
    "ld A, D",
    "ld A, E",
    "ld A, H",
    "ld A, L",
    "ld A, (HL)",
    "ld A, A",
    "add A, B",
    "add A, C",
    "add A, D",
    "add A, E",
    "add A, H",
    "add A, L",
    "add A, (HL)",
    "add A, A",
    "adc A, B",
    "adc A, C",
    "adc A, D",
    "adc A, E",
    "adc A, H",
    "adc A, L",
    "adc A, (HL)",
    "adc A, A",
    "sub A, B",
    "sub A, C",
    "sub A, D",
    "sub A, E",
    "sub A, H",
    "sub A, L",
    "sub A, (HL)",
    "sub A, A",
    "sbc A, B",
    "sbc A, C",
    "sbc A, D",
    "sbc A, E",
    "sbc A, H",
    "sbc A, L",
    "sbc A, (HL)",
    "sbc A, A",
    "and A, B",
    "and A, C",
    "and A, D",
    "and A, E",
    "and A, H",
    "and A, L",
    "and A, (HL)",
    "and A, A",
    "xor A, B",
    "xor A, C",
    "xor A, D",
    "xor A, E",
    "xor A, H",
    "xor A, L",
    "xor A, (HL)",
    "xor A, A",
    "or A, B",
    "or A, C",
    "or A, D",
    "or A, E",
    "or A, H",
    "or A, L",
    "or A, (HL)",
    "or A, A",
    "cp A, B",
    "cp A, C",
    "cp A, D",
    "cp A, E",
    "cp A, H",
    "cp A, L",
    "cp A, (HL)",
    "cp A, A",
    "ret NZ",
    "pop BC",
    "jp NZ, u16",
    "jp u16",
    "call NZ, u16",
    "push BC",
    "add A, u8",
    "rst 0x00",
    "ret Z",
    "ret",
    "jp Z, u16",
    "prefix CB",
    "call Z, u16",
    "call u16",
    "adc A, u8",
    "rst 0x08",
    "ret NC",
    "pop DE",
    "jp NC, u16",
    "invalid",
    "call NC, u16",
    "push DE",
    "sub A, u8",
    "rst 0x10",
    "ret C",
    "reti",
    "jp C, u16",
    "invalid",
    "call C, u16",
    "invalid",
    "sbc A, u8",
    "rst 0x18",
    "ld (0xff00 + u8), A",
    "pop HL",
    "ld (0xff00 + C), A",
    "invalid",
    "invalid",
    "push HL",
    "and A, u8",
    "rst 0x20",
    "add SP, i8",
    "jp HL",
    "ld (u16), A",
    "invalid",
    "invalid",
    "invalid",
    "xor A, u8",
    "rst 0x28",
    "ld A, (0xff00 + u8)",
    "pop AF",
    "ld A, (0xff00 + C)",
    "di",
    "invalid",
    "push AF",
    "or A, u8",
    "rst 0x30",
    "ld HL, SP+i8",
    "ld SP, HL",
    "ld A, (u16)",
    "ei",
    "invalid",
    "invalid",
    "cp A, u8",
    "rst 0x38",
};

static inline void debug_print_op(struct gb_s *gb, uint8_t op)
{
    printf("0x%04x:\n\t0x%02x: %s\n", gb->cpu.regs.pc, op, opcodes[op]);
    printf("\t\tA: 0x%02x B: 0x%02x C: 0x%02x D: 0x%02x E: 0x%02x "
            "F: 0x%02x H: 0x%02x L: 0x%02x\n", gb->cpu.regs.a,
            gb->cpu.regs.b, gb->cpu.regs.c, gb->cpu.regs.d, gb->cpu.regs.e,
            gb->cpu.regs.f, gb->cpu.regs.h, gb->cpu.regs.l);
    printf("\t\tAF: 0x%04x BC: 0x%04x DE: 0x%04x HL: 0x%04x\n",
            gb->cpu.regs.af, gb->cpu.regs.bc,
            gb->cpu.regs.de, gb->cpu.regs.hl);
    printf("\t\tPC: 0x%04x SP: 0x%04x\n", gb->cpu.regs.pc, gb->cpu.regs.sp);
    printf("\t\tZ: %ud N: %ud H: %ud C: %ud\n", get_flag_z, get_flag_n,
            get_flag_h, get_flag_c);
}

#endif /* !_BOI_DEBUG */

#endif /* !BOI_OPS_H */
