#include <stdbool.h>
#include <stdio.h>

#include "gb.h"
#include "irq.h"
#include "mem.h"
#include "ops.h"

/* Initialize CPU to default values */
void cpu_init(struct gb_s *gb)
{
    /* Set all registers to their initial value */
    gb->cpu.regs.af = 0x1b0;
    gb->cpu.regs.bc = 0x13;
    gb->cpu.regs.de = 0xd8;
    gb->cpu.regs.hl = 0x14d;

    gb->cpu.regs.sp = 0xfffe;
    gb->cpu.regs.pc = 0x100;

    /* We start in non-halted mode */
    gb->cpu.halted = false;

    /*
     * Although this will alredy be reset we do it out of convention when
     * setting all the fields in a structure
     */
    gb->cpu.cycles = 0;

    printf("CPU successfully initialized...\n");

    return;
}

/*
 * Here are all the operations after a 0xcb prefix.
 *
 * See the func_cb function for more details.
 *
 * TODO: handle default case
 */

static inline void func_rlc(struct gb_s *gb, uint8_t reg)
{
    uint8_t old;
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            old = gb->cpu.regs.b >> 7;
            gb->cpu.regs.b = gb->cpu.regs.b << 1 | old;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            old = gb->cpu.regs.c >> 7;
            gb->cpu.regs.c = gb->cpu.regs.c << 1 | old;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            old = gb->cpu.regs.d >> 7;
            gb->cpu.regs.d = gb->cpu.regs.d << 1 | old;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            old = gb->cpu.regs.e >> 7;
            gb->cpu.regs.e = gb->cpu.regs.e << 1 | old;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            old = gb->cpu.regs.h >> 7;
            gb->cpu.regs.h = gb->cpu.regs.h << 1 | old;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            old = gb->cpu.regs.l >> 7;
            gb->cpu.regs.l = gb->cpu.regs.l << 1 | old;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            old = tmp >> 7;
            tmp = tmp << 1 | old;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            old = gb->cpu.regs.a >> 7;
            gb->cpu.regs.a = gb->cpu.regs.a << 1 | old;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_c(old);
    set_flag_n(false);
    set_flag_h(false);
}

static inline void func_rrc(struct gb_s *gb, uint8_t reg)
{
    uint8_t old;
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            old = gb->cpu.regs.b & 0x1;
            gb->cpu.regs.b = gb->cpu.regs.b >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            old = gb->cpu.regs.c & 0x1;
            gb->cpu.regs.c = gb->cpu.regs.c >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            old = gb->cpu.regs.d & 0x1;
            gb->cpu.regs.d = gb->cpu.regs.d >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            old = gb->cpu.regs.e & 0x1;
            gb->cpu.regs.e = gb->cpu.regs.e >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            old = gb->cpu.regs.h & 0x1;
            gb->cpu.regs.h = gb->cpu.regs.h >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            old = gb->cpu.regs.l & 0x1;
            gb->cpu.regs.l = gb->cpu.regs.l >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            old = tmp & 0x1;
            tmp = tmp >> 1 | old << 7;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            old = gb->cpu.regs.a & 0x1;
            gb->cpu.regs.a = gb->cpu.regs.a >> 1 | old << 7;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_c(old);
    set_flag_n(false);
    set_flag_h(false);
}

static inline void func_rl(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;
    bool tmp_c = get_flag_c;

    switch(reg) {
        case 0x00: /* B */
            set_flag_c(gb->cpu.regs.b >> 7);
            gb->cpu.regs.b = gb->cpu.regs.b << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            set_flag_c(gb->cpu.regs.c >> 7);
            gb->cpu.regs.c = gb->cpu.regs.c << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            set_flag_c(gb->cpu.regs.d >> 7);
            gb->cpu.regs.d = gb->cpu.regs.d << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            set_flag_c(gb->cpu.regs.e >> 7);
            gb->cpu.regs.e = gb->cpu.regs.e << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            set_flag_c(gb->cpu.regs.h >> 7);
            gb->cpu.regs.h = gb->cpu.regs.h << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            set_flag_c(gb->cpu.regs.l >> 7);
            gb->cpu.regs.l = gb->cpu.regs.l << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            set_flag_c(tmp >> 7);
            tmp = tmp << 1 | tmp_c;
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            set_flag_c(gb->cpu.regs.a >> 7);
            gb->cpu.regs.a = gb->cpu.regs.a << 1 | tmp_c;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_n(false);
    set_flag_h(false);
}

static inline void func_rr(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;
    bool tmp_c = get_flag_c;

    switch(reg) {
        case 0x00: /* B */
            set_flag_c(gb->cpu.regs.b & 0x1);
            gb->cpu.regs.b = gb->cpu.regs.b >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            set_flag_c(gb->cpu.regs.c & 0x1);
            gb->cpu.regs.c = gb->cpu.regs.c >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            set_flag_c(gb->cpu.regs.d & 0x1);
            gb->cpu.regs.d = gb->cpu.regs.d >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            set_flag_c(gb->cpu.regs.e & 0x1);
            gb->cpu.regs.e = gb->cpu.regs.e >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            set_flag_c(gb->cpu.regs.h & 0x1);
            gb->cpu.regs.h = gb->cpu.regs.h >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            set_flag_c(gb->cpu.regs.l & 0x1);
            gb->cpu.regs.l = gb->cpu.regs.l >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            set_flag_c(tmp & 0x1);
            tmp = tmp >> 1 | tmp_c << 7;;
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            set_flag_c(gb->cpu.regs.a & 0x1);
            gb->cpu.regs.a = gb->cpu.regs.a >> 1 | tmp_c << 7;;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_n(false);
    set_flag_h(false);
}

static inline void func_sla(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            set_flag_c(gb->cpu.regs.b >> 7);
            gb->cpu.regs.b <<= 1;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            set_flag_c(gb->cpu.regs.c >> 7);
            gb->cpu.regs.c <<= 1;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            set_flag_c(gb->cpu.regs.d >> 7);
            gb->cpu.regs.d <<= 1;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            set_flag_c(gb->cpu.regs.e >> 7);
            gb->cpu.regs.e <<= 1;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            set_flag_c(gb->cpu.regs.h >> 7);
            gb->cpu.regs.h <<= 1;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            set_flag_c(gb->cpu.regs.l >> 7);
            gb->cpu.regs.l <<= 1;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            set_flag_c(tmp >> 7);
            tmp <<= 1;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            set_flag_c(gb->cpu.regs.a >> 7);
            gb->cpu.regs.a <<= 1;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_h(false);
    set_flag_n(false);
}

static inline void func_sra(struct gb_s *gb, uint8_t reg)
{
    uint8_t old;
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            set_flag_c(gb->cpu.regs.b & 0x01);
            old = gb->cpu.regs.b & 0x80;
            gb->cpu.regs.b = gb->cpu.regs.b >> 1 | old;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            set_flag_c(gb->cpu.regs.c & 0x01);
            old = gb->cpu.regs.c & 0x80;
            gb->cpu.regs.c = gb->cpu.regs.c >> 1 | old;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            set_flag_c(gb->cpu.regs.d & 0x01);
            old = gb->cpu.regs.d & 0x80;
            gb->cpu.regs.d = gb->cpu.regs.d >> 1 | old;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            set_flag_c(gb->cpu.regs.e & 0x01);
            old = gb->cpu.regs.e & 0x80;
            gb->cpu.regs.e = gb->cpu.regs.e >> 1 | old;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            set_flag_c(gb->cpu.regs.h & 0x01);
            old = gb->cpu.regs.h & 0x80;
            gb->cpu.regs.h = gb->cpu.regs.h >> 1 | old;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            set_flag_c(gb->cpu.regs.l & 0x01);
            old = gb->cpu.regs.l & 0x80;
            gb->cpu.regs.l = gb->cpu.regs.l >> 1 | old;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            set_flag_c(tmp & 0x01);
            old = tmp & 0x80;
            tmp = tmp >> 1 | old;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            set_flag_c(gb->cpu.regs.a & 0x01);
            old = gb->cpu.regs.a & 0x80;
            gb->cpu.regs.a = gb->cpu.regs.a >> 1 | old;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_h(false);
    set_flag_n(false);
}

static inline void func_swap(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            gb->cpu.regs.b = gb->cpu.regs.b << 4 | gb->cpu.regs.b >> 4;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            gb->cpu.regs.c = gb->cpu.regs.c << 4 | gb->cpu.regs.c >> 4;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            gb->cpu.regs.d = gb->cpu.regs.d << 4 | gb->cpu.regs.d >> 4;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            gb->cpu.regs.e = gb->cpu.regs.e << 4 | gb->cpu.regs.e >> 4;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            gb->cpu.regs.h = gb->cpu.regs.h << 4 | gb->cpu.regs.h >> 4;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            gb->cpu.regs.l = gb->cpu.regs.l << 4 | gb->cpu.regs.l >> 4;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            tmp = tmp << 4 | tmp >> 4;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.regs.a = gb->cpu.regs.a << 4 | gb->cpu.regs.a >> 4;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_n(false);
    set_flag_h(false);
    set_flag_c(false);
}

static inline void func_srl(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            set_flag_c(gb->cpu.regs.b & 0x01);
            gb->cpu.regs.b >>= 1;
            set_flag_z(!gb->cpu.regs.b);
            break;
        case 0x01: /* C */
            set_flag_c(gb->cpu.regs.c & 0x01);
            gb->cpu.regs.c >>= 1;
            set_flag_z(!gb->cpu.regs.c);
            break;
        case 0x02: /* D */
            set_flag_c(gb->cpu.regs.d & 0x01);
            gb->cpu.regs.d >>= 1;
            set_flag_z(!gb->cpu.regs.d);
            break;
        case 0x03: /* E */
            set_flag_c(gb->cpu.regs.e & 0x01);
            gb->cpu.regs.e >>= 1;
            set_flag_z(!gb->cpu.regs.e);
            break;
        case 0x04: /* H */
            set_flag_c(gb->cpu.regs.h & 0x01);
            gb->cpu.regs.h >>= 1;
            set_flag_z(!gb->cpu.regs.h);
            break;
        case 0x05: /* L */
            set_flag_c(gb->cpu.regs.l & 0x01);
            gb->cpu.regs.l >>= 1;
            set_flag_z(!gb->cpu.regs.l);
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            set_flag_c(tmp & 0x01);
            tmp >>= 1;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            set_flag_z(!tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            set_flag_c(gb->cpu.regs.a & 0x01);
            gb->cpu.regs.a >>= 1;
            set_flag_z(!gb->cpu.regs.a);
            break;
    }
    set_flag_h(false);
    set_flag_n(false);
}

static inline void func_bit(struct gb_s *gb, uint8_t reg, uint8_t mask)
{
    switch(reg) {
        case 0x00: /* B */
            set_flag_z(!(gb->cpu.regs.b & mask));
            break;
        case 0x01: /* C */
            set_flag_z(!(gb->cpu.regs.c & mask));
            break;
        case 0x02: /* D */
            set_flag_z(!(gb->cpu.regs.d & mask));
            break;
        case 0x03: /* E */
            set_flag_z(!(gb->cpu.regs.e & mask));
            break;
        case 0x04: /* H */
            set_flag_z(!(gb->cpu.regs.h & mask));
            break;
        case 0x05: /* L */
            set_flag_z(!(gb->cpu.regs.l & mask));
            break;
        case 0x06: /* (HL) */
            set_flag_z(!(mem_read_byte(gb, gb->cpu.regs.hl) & mask));
            gb->cpu.cycles += 1;
            break;
        case 0x07: /* A */
            set_flag_z(!(gb->cpu.regs.a & mask));
            break;
    }
    set_flag_n(false);
    set_flag_h(true);
}

static inline void func_res(struct gb_s *gb, uint8_t reg, uint8_t mask)
{
    uint8_t tmp;
    switch(reg) {
        case 0x00: /* B */
            gb->cpu.regs.b |= mask;
            break;
        case 0x01: /* C */
            gb->cpu.regs.c |= mask;
            break;
        case 0x02: /* D */
            gb->cpu.regs.d |= mask;
            break;
        case 0x03: /* E */
            gb->cpu.regs.e |= mask;
            break;
        case 0x04: /* H */
            gb->cpu.regs.h |= mask;
            break;
        case 0x05: /* L */
            gb->cpu.regs.l |= mask;
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            tmp |= mask;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.regs.a |= mask;
            break;
    }
}

static inline void func_set(struct gb_s *gb, uint8_t reg, uint8_t mask)
{
    uint8_t tmp;
    switch(reg) {
        case 0x00: /* B */
            gb->cpu.regs.b |= mask;
            break;
        case 0x01: /* C */
            gb->cpu.regs.c |= mask;
            break;
        case 0x02: /* D */
            gb->cpu.regs.d |= mask;
            break;
        case 0x03: /* E */
            gb->cpu.regs.e |= mask;
            break;
        case 0x04: /* H */
            gb->cpu.regs.h |= mask;
            break;
        case 0x05: /* L */
            gb->cpu.regs.l |= mask;
            break;
        case 0x06: /* (HL) */
            tmp = mem_read_byte(gb, gb->cpu.regs.hl);
            tmp |= mask;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.regs.a |= mask;
            break;
    }
}

/*
 * These are all the static inline functions called in the *big* switch later.
 *
 * For the sake of simplicity there is one function for unhandled opcodes,
 * one for invalid opcodes and then one function for each opcode.
 *
 * All the opcode functions are named:
 *      func_xx
 *
 * where xx is the lower case hex representation of the opcode.
 */

/* invalid */
static inline void func_invalid(uint8_t op)
{
    fprintf(stderr, "Error: invalid opcode:  0x%02x\n", op);
}

/* nop */
static inline void func_00(struct gb_s *gb)
{
    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld BC, u16 */
static inline void func_01(struct gb_s *gb)
{
    gb->cpu.regs.bc = mem_read_word(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 3;
}

/* ld (BC), A */
static inline void func_02(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.bc, gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc BC */
static inline void func_03(struct gb_s *gb)
{
    ++gb->cpu.regs.bc;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc B */
static inline void func_04(struct gb_s *gb)
{
    set_flag_h((gb->cpu.regs.b & 0xf) == 0xf);
    ++gb->cpu.regs.b;
    set_flag_z(!gb->cpu.regs.b);
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec B */
static inline void func_05(struct gb_s *gb)
{
    --gb->cpu.regs.b;
    set_flag_z(!gb->cpu.regs.b);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.b & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, u8 */
static inline void func_06(struct gb_s *gb)
{
    gb->cpu.regs.b = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rlca */
static inline void func_07(struct gb_s *gb)
{
    func_rlc(gb, 0x7);
    set_flag_z(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld (u16), SP */
static inline void func_08(struct gb_s *gb)
{
    uint16_t off = mem_read_word(gb, gb->cpu.regs.pc + 1);
    mem_write_word(gb, off, gb->cpu.regs.sp);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 5;
}

/* add HL, BC */
/* TODO: there is probably a better way to check for H and C but it is late
 * and I want to sleep.
 */
static inline void func_09(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.hl + gb->cpu.regs.bc;
    set_flag_n(false);
    set_flag_c(tmp > 0xffff);
    set_flag_h((tmp & 0xffff) < (gb->cpu.regs.hl & 0xffff));
    gb->cpu.regs.hl = tmp & 0xffff;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld A, (BC) */
static inline void func_0a(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, gb->cpu.regs.bc);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec BC */
static inline void func_0b(struct gb_s *gb)
{
    --gb->cpu.regs.bc;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 2;
}

/* inc C */
static inline void func_0c(struct gb_s *gb)
{
    set_flag_h((gb->cpu.regs.c & 0xf) == 0xf);
    ++gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.c);
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec C */
static inline void func_0d(struct gb_s *gb)
{
    --gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.c);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.c & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, u8 */
static inline void func_0e(struct gb_s *gb)
{
    gb->cpu.regs.hl = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rrca */
static inline void func_0f(struct gb_s *gb)
{
    /* Call rrc with A register */
    func_rrc(gb, 0x7);
    set_flag_z(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* stop */
/* TODO: handle STOP opcode */
static inline void func_10(void)
{
    func_invalid(0x10);
}

/* ld DE, u16 */
static inline void func_11(struct gb_s *gb)
{
    gb->cpu.regs.de = mem_read_word(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 3;
}

/* ld (DE), A */
static inline void func_12(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.de, gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc DE */
static inline void func_13(struct gb_s *gb)
{
    ++gb->cpu.regs.de;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc D */
static inline void func_14(struct gb_s *gb)
{
    set_flag_h((gb->cpu.regs.d & 0xf) == 0xf);
    ++gb->cpu.regs.d;
    set_flag_z(!gb->cpu.regs.d);
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec D */
static inline void func_15(struct gb_s *gb)
{
    --gb->cpu.regs.d;
    set_flag_z(!gb->cpu.regs.d);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.d & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, u8 */
static inline void func_16(struct gb_s *gb)
{
    gb->cpu.regs.d = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rla */
static inline void func_17(struct gb_s *gb)
{
    /* Call rl function with register A */
    func_rl(gb, 0x7);
    set_flag_z(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* jr rel8 */
static inline void func_18(struct gb_s *gb)
{
    gb->cpu.cycles += 3;
    gb->cpu.regs.pc += (int8_t) mem_read_byte(gb, gb->cpu.regs.pc + 1) + 2;
}

/* add HL, DE */
static inline void func_19(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.hl + gb->cpu.regs.de;
    set_flag_n(false);
    set_flag_c(tmp > 0xffff);
    set_flag_h((tmp & 0xffff) < (gb->cpu.regs.hl & 0xffff));
    gb->cpu.regs.hl = tmp & 0xffff;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld A, (DE) */
static inline void func_1a(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, gb->cpu.regs.de);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec DE */
static inline void func_1b(struct gb_s *gb)
{
    --gb->cpu.regs.de;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 2;
}

/* inc E */
static inline void func_1c(struct gb_s *gb)
{
    set_flag_h((gb->cpu.regs.e & 0xf) == 0xf);
    ++gb->cpu.regs.e;
    set_flag_z(!gb->cpu.regs.e);
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec E */
static inline void func_1d(struct gb_s *gb)
{
    --gb->cpu.regs.e;
    set_flag_z(!gb->cpu.regs.e);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.e & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, u8 */
static inline void func_1e(struct gb_s *gb)
{
    gb->cpu.regs.e = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rra */
static inline void func_1f(struct gb_s *gb)
{
    /* Call rr function with register A */
    func_rr(gb, 0x7);
    set_flag_z(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* jr NZ, rel8 */
static inline void func_20(struct gb_s *gb)
{
    if (!get_flag_z) {
        /* TODO: check the +2 here is right skipping operands */
        gb->cpu.regs.pc += (int8_t) mem_read_byte(gb, gb->cpu.regs.pc + 1) + 2;
        gb->cpu.cycles += 3;
    } else {
        gb->cpu.regs.pc += 2;
        gb->cpu.cycles += 2;
    }

}

/* ld HL, u16 */
static inline void func_21(struct gb_s *gb)
{
    gb->cpu.regs.hl = mem_read_word(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 3;
}

/* ldi (HL), A */
static inline void func_22(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl++, gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc HL */
static inline void func_23(struct gb_s *gb)
{
    ++gb->cpu.regs.hl;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc H */
static inline void func_24(struct gb_s *gb)
{
    ++gb->cpu.regs.h;
    set_flag_z(!gb->cpu.regs.h);
    set_flag_h(!(gb->cpu.regs.h & 0x0f));
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* dec H */
static inline void func_25(struct gb_s *gb)
{
    --gb->cpu.regs.h;
    set_flag_z(!gb->cpu.regs.h);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.h & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, u8 */
static inline void func_26(struct gb_s *gb)
{
    gb->cpu.regs.h = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* daa */
static inline void func_27(struct gb_s *gb)
{
    uint16_t tmp = gb->cpu.regs.a;

    if (get_flag_n) {
        if (get_flag_h)
            tmp = (tmp - 0x06) & 0xff;
        if (get_flag_c)
            tmp -= 0x60;
    } else {
        if (get_flag_h || (tmp & 0xf) > 9)
            tmp += 0x06;
        if (get_flag_c || tmp > 0x9f)
            tmp += 0x60;
    }

    gb->cpu.regs.a = tmp;
    set_flag_h(false);
    set_flag_z(!gb->cpu.regs.a);
    if (tmp > 0xff)
        set_flag_c(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* jr Z, rel8 */
static inline void func_28(struct gb_s *gb)
{
    if (get_flag_z) {
        /* TODO: check the +2 here is right skipping operands */
        gb->cpu.regs.pc += (int8_t) mem_read_byte(gb,
                gb->mem.raw[gb->cpu.regs.pc + 1]) + 2;
        gb->cpu.cycles += 3;
    } else {
        gb->cpu.regs.pc += 2;
        gb->cpu.cycles += 2;
    }
}

/* add HL, HL */
static inline void func_29(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.hl << 1;
    set_flag_n(false);
    set_flag_c(tmp > 0xffff);
    set_flag_h((tmp & 0xffff) < (gb->cpu.regs.hl & 0xffff));
    gb->cpu.regs.hl = tmp & 0xffff;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ldi A, (HL) */
static inline void func_2a(struct gb_s *gb)
{
    gb->cpu.regs.a  = mem_read_byte(gb, gb->cpu.regs.hl++);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec HL */
static inline void func_2b(struct gb_s *gb)
{
    --gb->cpu.regs.hl;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 2;
}

/* inc L */
static inline void func_2c(struct gb_s *gb)
{
    ++gb->cpu.regs.l;
    set_flag_z(!gb->cpu.regs.l);
    set_flag_h(!(gb->cpu.regs.l & 0x0f));
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* dec L */
static inline void func_2d(struct gb_s *gb)
{
    --gb->cpu.regs.l;
    set_flag_z(!gb->cpu.regs.l);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.l & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, u8 */
static inline void func_2e(struct gb_s *gb)
{
    gb->cpu.regs.l = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* cpl */
static inline void func_2f(struct gb_s *gb)
{
    gb->cpu.regs.a = ~gb->cpu.regs.a;

    set_flag_n(true);
    set_flag_h(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* jr NC, rel8 */
static inline void func_30(struct gb_s *gb)
{
    /* TODO: check this +2 to skip instr and opcode is right */
    if (!get_flag_c) {
        gb->cpu.regs.pc += (int8_t) mem_read_byte(gb, gb->cpu.regs.pc + 1) + 2;
        gb->cpu.cycles += 3;
    } else {
        gb->cpu.regs.pc += 2;
        gb->cpu.cycles += 2;
    }
}

/* ld SP, u16 */
static inline void func_31(struct gb_s *gb)
{
    gb->cpu.regs.sp = mem_read_word(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 3;
}

/* ldd (HL), A */
static inline void func_32(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.a);
    --gb->cpu.regs.hl;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc SP */
static inline void func_33(struct gb_s *gb)
{
    ++gb->cpu.regs.sp;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* inc (HL) */
static inline void func_34(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    tmp++;
    mem_write_byte(gb, gb->cpu.regs.hl, tmp);
    set_flag_z(!tmp);
    set_flag_n(false);
    set_flag_h((tmp & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* dec (HL) */
static inline void func_35(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    tmp--;
    mem_write_byte(gb, gb->cpu.regs.hl, tmp);
    set_flag_z(!tmp);
    set_flag_n(true);
    set_flag_h((tmp & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* ld (HL), u8 */
static inline void func_36(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    mem_write_byte(gb, gb->cpu.regs.hl, tmp);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;
}

/* scf */
static inline void func_37(struct gb_s *gb)
{
    set_flag_n(false);
    set_flag_h(false);
    set_flag_c(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* jr C, rel8 */
static inline void func_38(struct gb_s *gb)
{
    /* TODO: check this +2 to skip instr and opcode is right */
    if (get_flag_c) {
        gb->cpu.regs.pc += (int8_t) mem_read_byte(gb, gb->cpu.regs.pc + 1) + 2;
        gb->cpu.cycles += 3;
    } else {
        gb->cpu.regs.pc += 2;
        gb->cpu.cycles += 2;
    }
}

/* add HL, SP */
static inline void func_39(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.hl + gb->cpu.regs.sp;
    set_flag_n(false);
    set_flag_c(tmp > 0xffff);
    set_flag_h((tmp & 0xffff) < (gb->cpu.regs.hl & 0xffff));
    gb->cpu.regs.hl = tmp & 0xffff;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ldd A, (HL) */
static inline void func_3a(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, gb->cpu.regs.hl--);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* dec SP */
static inline void func_3b(struct gb_s *gb)
{
    --gb->cpu.regs.sp;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 2;
}

/* inc A */
static inline void func_3c(struct gb_s *gb)
{
    ++gb->cpu.regs.a;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(!(gb->cpu.regs.a & 0x0f));
    set_flag_n(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* dec A */
static inline void func_3d(struct gb_s *gb)
{
    --gb->cpu.regs.a;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);
    set_flag_h((gb->cpu.regs.a & 0xf) == 0xf);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, u8 */
static inline void func_3e(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* ccf */
static inline void func_3f(struct gb_s *gb)
{
    set_flag_n(false);
    set_flag_h(false);
    set_flag_c(!get_flag_c);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, B */
static inline void func_40(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, C */
static inline void func_41(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, D */
static inline void func_42(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, E */
static inline void func_43(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, H */
static inline void func_44(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, L */
static inline void func_45(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld B, (HL) */
static inline void func_46(struct gb_s *gb)
{
    gb->cpu.regs.b = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld B, A */
static inline void func_47(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, B */
static inline void func_48(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, C */
static inline void func_49(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, D */
static inline void func_4a(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, E */
static inline void func_4b(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, H */
static inline void func_4c(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, L */
static inline void func_4d(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld C, (HL) */
static inline void func_4e(struct gb_s *gb)
{
    gb->cpu.regs.c = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld C, A */
static inline void func_4f(struct gb_s *gb)
{
    gb->cpu.regs.c = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, B */
static inline void func_50(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, C */
static inline void func_51(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, D */
static inline void func_52(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, E */
static inline void func_53(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, H */
static inline void func_54(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, L */
static inline void func_55(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld D, (HL) */
static inline void func_56(struct gb_s *gb)
{
    gb->cpu.regs.d = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld D, A */
static inline void func_57(struct gb_s *gb)
{
    gb->cpu.regs.d = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, B */
static inline void func_58(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, C */
static inline void func_59(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, D */
static inline void func_5a(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, E */
static inline void func_5b(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, H */
static inline void func_5c(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, L */
static inline void func_5d(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld E, (HL) */
static inline void func_5e(struct gb_s *gb)
{
    gb->cpu.regs.e = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld E, A */
static inline void func_5f(struct gb_s *gb)
{
    gb->cpu.regs.e = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, B */
static inline void func_60(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, C */
static inline void func_61(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, D */
static inline void func_62(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, E */
static inline void func_63(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, H */
static inline void func_64(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, L */
static inline void func_65(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld H, (HL) */
static inline void func_66(struct gb_s *gb)
{
    gb->cpu.regs.h = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld H, A */
static inline void func_67(struct gb_s *gb)
{
    gb->cpu.regs.h = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, B */
static inline void func_68(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, C */
static inline void func_69(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, D */
static inline void func_6a(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, E */
static inline void func_6b(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, H */
static inline void func_6c(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, L */
static inline void func_6d(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld L, (HL) */
static inline void func_6e(struct gb_s *gb)
{
    gb->cpu.regs.l = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld L, A */
static inline void func_6f(struct gb_s *gb)
{
    gb->cpu.regs.l = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld (HL), B */
static inline void func_70(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.b);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld (HL), C */
static inline void func_71(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.c);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld (HL), D */
static inline void func_72(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.d);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld (HL), E */
static inline void func_73(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.e);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld (HL), H */
static inline void func_74(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.h);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld (HL), L */
static inline void func_75(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.l);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* halt */
static inline void func_76(struct gb_s *gb)
{
    gb->cpu.halted = true;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld (HL), A */
static inline void func_77(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.hl, gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld A, B */
static inline void func_78(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.b;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, C */
static inline void func_79(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.c;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, D */
static inline void func_7a(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.d;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, E */
static inline void func_7b(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.e;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, H */
static inline void func_7c(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.h;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, L */
static inline void func_7d(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.l;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ld A, (HL) */
static inline void func_7e(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld A, A */
static inline void func_7f(struct gb_s *gb)
{
    gb->cpu.regs.a = gb->cpu.regs.a;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add B */
static inline void func_80(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.b;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.b & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add C */
static inline void func_81(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.c;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.c & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add D */
static inline void func_82(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.d;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.d & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add E */
static inline void func_83(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.e;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.e & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add H */
static inline void func_84(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.h;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.h & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add L */
static inline void func_85(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.l;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.l & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* add (HL) */
static inline void func_86(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + mem_read_byte(gb, gb->cpu.regs.hl);

    set_flag_h((tmp & 0xf) < (gb->cpu.regs.a & 0xf));
    set_flag_c(tmp > 0xff);
    set_flag_n(false);
    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* add A */
static inline void func_87(struct gb_s *gb)
{
    uint32_t tmp = gb->cpu.regs.a + gb->cpu.regs.a;
    set_flag_h((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.a & 0xf) > 0xf);
    set_flag_c(tmp > 0xff);
    set_flag_n(false);

    gb->cpu.regs.a = tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc B */
static inline void func_88(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.b + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.b & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.b + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc C */
static inline void func_89(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.c + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.c & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.c + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc D */
static inline void func_8a(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.d + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.d & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.d + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc E */
static inline void func_8b(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.e + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.e & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.e + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc H */
static inline void func_8c(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.h + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.h & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.h + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc L */
static inline void func_8d(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.l + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.l & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.l + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* adc (HL) */
static inline void func_8e(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    uint32_t tmp2 = gb->cpu.regs.a + tmp + get_flag_c > 0xff;

    set_flag_n(false);
    set_flag_h((gb->cpu.regs.a & 0xf) + (tmp & 0xf) + get_flag_c > 0xf);

    gb->cpu.regs.a += tmp + get_flag_c;
    set_flag_c(tmp2);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* adc A */
static inline void func_8f(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + gb->cpu.regs.a + get_flag_z > 0xff;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (gb->cpu.regs.a & 0xf) + get_flag_z)
            > 0xf);
    gb->cpu.regs.a += gb->cpu.regs.a + get_flag_c;
    set_flag_c(tmp);
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub B */
static inline void func_90(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.b) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.b) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub C */
static inline void func_91(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.c) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.c) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub D */
static inline void func_92(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.d) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.d) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub E */
static inline void func_93(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.b) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.b) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub H */
static inline void func_94(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.h) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.h) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub L */
static inline void func_95(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.l) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.l) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sub (HL) */
static inline void func_96(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    set_flag_c((gb->cpu.regs.a - tmp) < 0);
    set_flag_h(((gb->cpu.regs.a - tmp) & 0xf) > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* sub A */
static inline void func_97(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.a) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.a) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc B */
static inline void func_98(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.b + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.b & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.b - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc C */
static inline void func_99(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.c + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.c & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.c - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc D */
static inline void func_9a(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.d + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.d & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.d - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc E */
static inline void func_9b(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.e + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.e & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.e - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc H */
static inline void func_9c(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.h + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.h & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.h - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc L */
static inline void func_9d(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.l + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.l & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.l - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* sbc (HL) */
static inline void func_9e(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    bool tmp_bool = get_flag_c + tmp;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (tmp & 0xf) - get_flag_c) < 0);
    set_flag_c((gb->cpu.regs.a - tmp - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp_bool;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* sbc A */
static inline void func_9f(struct gb_s *gb)
{
    uint8_t tmp = gb->cpu.regs.a + get_flag_c;
    set_flag_h(((gb->cpu.regs.a & 0xf) - (gb->cpu.regs.a & 0xf) - get_flag_c)
            < 0);
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.a - get_flag_c) < 0);
    set_flag_n(true);
    gb->cpu.regs.a -= tmp;
    set_flag_z(!gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and B */
static inline void func_a0(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.b;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and C */
static inline void func_a1(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and D */
static inline void func_a2(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.d;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and E */
static inline void func_a3(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.e;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and H */
static inline void func_a4(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.h;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and L */
static inline void func_a5(struct gb_s *gb)
{
    gb->cpu.regs.a &= gb->cpu.regs.l;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* and (HL) */
static inline void func_a6(struct gb_s *gb)
{
    gb->cpu.regs.a &= mem_read_byte(gb, gb->cpu.regs.hl);
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* and A */
static inline void func_a7(struct gb_s *gb)
{
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(true);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor B */
static inline void func_a8(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.b;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor C */
static inline void func_a9(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor D */
static inline void func_aa(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.d;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor E */
static inline void func_ab(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.e;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor H */
static inline void func_ac(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.h;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor L */
static inline void func_ad(struct gb_s *gb)
{
    gb->cpu.regs.a ^= gb->cpu.regs.l;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* xor (HL) */
static inline void func_ae(struct gb_s *gb)
{
    gb->cpu.regs.a ^= mem_read_byte(gb, gb->cpu.regs.hl);
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* xor A */
static inline void func_af(struct gb_s *gb)
{
    gb->cpu.regs.a = 0;

    set_flag_z(true);
    set_flag_n(false);
    set_flag_h(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or B */
static inline void func_b0(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.b;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or C */
static inline void func_b1(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.c;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or D */
static inline void func_b2(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.d;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or E */
static inline void func_b3(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.e;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or H */
static inline void func_b4(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.h;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or L */
static inline void func_b5(struct gb_s *gb)
{
    gb->cpu.regs.a |= gb->cpu.regs.l;
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* or (HL) */
static inline void func_b6(struct gb_s *gb)
{
    gb->cpu.regs.a |= mem_read_byte(gb, gb->cpu.regs.hl);
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* or A */
static inline void func_b7(struct gb_s *gb)
{
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp B */
static inline void func_b8(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.b) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.b) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.b);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp C */
static inline void func_b9(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.c) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.c) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.c);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp D */
static inline void func_ba(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.d) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.d) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.d);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp E */
static inline void func_bb(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.e) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.e) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.e);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp H */
static inline void func_bc(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.h) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.h) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.h);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp L */
static inline void func_bd(struct gb_s *gb)
{
    set_flag_c((gb->cpu.regs.a - gb->cpu.regs.l) < 0);
    set_flag_h(((gb->cpu.regs.a - gb->cpu.regs.l) & 0xf)
            > (gb->cpu.regs.a & 0xf));
    set_flag_z(gb->cpu.regs.a == gb->cpu.regs.l);
    set_flag_n(true);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* cp (HL) */
static inline void func_be(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.hl);
    set_flag_z(gb->cpu.regs.a == tmp);
    set_flag_h(((gb->cpu.regs.a - tmp) & 0xf) > (gb->cpu.regs.a & 0xf));
    set_flag_n(true);
    set_flag_c((gb->cpu.regs.a - tmp) < 0);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* cp A */
static inline void func_bf(struct gb_s *gb)
{
    set_flag_z(true);
    set_flag_h(false);
    set_flag_n(true);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* ret NZ */
static inline void func_c0(struct gb_s *gb)
{
    if (!get_flag_z) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);
        gb->cpu.regs.sp += 2;
        gb->cpu.cycles += 5;
    } else {
        ++gb->cpu.regs.pc;
        gb->cpu.cycles += 2;
    }
}

/* pop BC */
static inline void func_c1(struct gb_s *gb)
{
    gb->cpu.regs.bc = mem_read_word(gb, gb->cpu.regs.sp);

    gb->cpu.regs.sp += 2;
    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* jp NZ, mem16 */
static inline void func_c2(struct gb_s *gb)
{
    if (!get_flag_z) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);
        gb->cpu.cycles += 4;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* jp u16 */
static inline void func_c3(struct gb_s *gb)
{
    /* TODO: check we are not out of bounds */
    gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);
    gb->cpu.cycles += 4;

}

/* call NZ, u16 */
static inline void func_c4(struct gb_s *gb)
{
    if (!get_flag_z) {
        gb->cpu.regs.sp -= 2;
        /* Skip the current instr and it's two byte operand and push next instr */
        mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);

        gb->cpu.regs.pc = mem_read_byte(gb, gb->cpu.regs.pc + 1);
        gb->cpu.cycles += 6;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* push BC */
static inline void func_c5(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.bc);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 4;
}

/* add A, u8 */
static inline void func_c6(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    set_flag_c((gb->cpu.regs.a + tmp) > 0xff);
    set_flag_h(((gb->cpu.regs.a + tmp) & 0xf) < (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a += tmp;
    set_flag_n(false);
    set_flag_z(!gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rst 00 */
static inline void func_c7(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0;
    gb->cpu.cycles += 4;
}

/* ret Z */
static inline void func_c8(struct gb_s *gb)
{
    if (get_flag_z) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);

        gb->cpu.regs.sp += 2;
        gb->cpu.cycles += 5;
    } else {
        ++gb->cpu.regs.pc;
        gb->cpu.cycles += 2;
    }
}

/* ret */
static inline void func_c9(struct gb_s *gb)
{
    gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);

    gb->cpu.regs.sp += 2;
    gb->cpu.cycles += 4;
}

/* jp z, mem16 */
static inline void func_ca(struct gb_s *gb)
{
    if (get_flag_z) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);
        gb->cpu.cycles += 4;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/*
 * 0xcb is a prefix opcode which allows the use of 256 other opcodes.
 *
 * We read the real one-byte opcode from PC + 1 and it looks like this:
 *
 *      00000xxx => rlc xxx
 *      00001xxx => rrc xxx
 *      00010xxx => rl xxx
 *      00011xxx => rr xxx
 *      00100xxx => sla xxx
 *      00101xxx => sra xxx
 *      00110xxx => swap xxx
 *      00111xxx => srl xxx
 *      01yyyxxx => bit yyy, xxx
 *      10yyyxxx => res yyy, xxx
 *      11yyyxxx => set yyy, xxx
 *
 * where xxx encodes a register as follows:
 *
 *      000: B
 *      001: C
 *      010: D
 *      011: E
 *      100: H
 *      101: L
 *      110: (HL)
 *      111: A
 *
 * When present, yyy is the index of the bit to operate on.
 *
 */
static inline void func_cb(struct gb_s *gb)
{
    uint8_t op;
    uint8_t reg;
    uint8_t bit;

    /* Opcodes will last at least 2 cycles and are all of length 2 bytes */
    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;

    op = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    /* Get register and check if it is a single operand opcode */
    reg = op & 0x07;
    op >>= 3;

    /* It is, call function and return */
    if (op < 0x08) {

#ifdef _BOI_DEBUG
        printf("\tCB: 0x%02x, Register: 0x%02x\n", op, reg);
#endif /* !_BOI_DEBUG */

        switch (op) {
            case 0x00: /* rlc */
                func_rlc(gb, reg);
                return;
            case 0x01: /* rrc */
                func_rrc(gb, reg);
                return;
            case 0x02: /* rl */
                func_rl(gb, reg);
                return;
            case 0x03: /* rr */
                func_rr(gb, reg);
                return;
            case 0x04: /* sla */
                func_sla(gb, reg);
                return;
            case 0x05: /* sra */
                func_sra(gb, reg);
                return;
            case 0x06: /* swap */
                func_swap(gb, reg);
                return;
            case 0x07: /* srl */
                func_srl(gb, reg);
                return;
            default: /* invalid */
                fprintf(stderr, "Invalid CB opcode 0x%02x\n", op);
                return;
        }
    }

    /* It's a double operand opcode, decode bit index and call function */
    bit = op & 0x0f;
    op >>= 3;

#ifdef _BOI_DEBUG
    printf("\tCB: 0x%02x, Register: 0x%02x, Bit: 0x%02x\n", op, reg, bit);
#endif /* !_BOI_DEBUG */

    /*
     * An opcode id is always between 1 and 3 so op - 1 is the index.
     * 1 << bit creates the mask for the bit operation.
     */
    switch (op) {
        case 0x01: /* bit */
            func_bit(gb, reg, 1 << bit);
            return;
        case 0x02: /* res */
            func_res(gb, reg, 1 << bit);
            return;
        case 0x03: /* set */
            func_set(gb, reg, 1 << bit);
            return;
        default: /* invalid */
            fprintf(stderr, "Invalid CB opcode 0x%02x\n", op);
            return;
    }
}

/* call Z, u16 */
static inline void func_cc(struct gb_s *gb)
{
    if (get_flag_z) {
        gb->cpu.regs.sp -= 2;
        mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);

        gb->cpu.cycles += 6;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* call u16 */
static inline void func_cd(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;

    /* Skip the current instr and it's two byte operand and push next instr */
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);

    gb->cpu.regs.pc = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.cycles += 6;
}

/* adc a, u8 */
static inline void func_ce(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    bool tmp_bool = gb->cpu.regs.a + tmp + get_flag_c >= 0x100;
    set_flag_n(false);
    set_flag_h(((gb->cpu.regs.a & 0xf) + (tmp & 0xf) + get_flag_c) >= 0x10);

    gb->cpu.regs.a += tmp + get_flag_c;

    set_flag_c(tmp_bool);
    set_flag_z(!gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rst 08 */
static inline void func_cf(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x08;
    gb->cpu.cycles += 4;
}

/* ret NC */
static inline void func_d0(struct gb_s *gb)
{
    if (!get_flag_c) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);

        gb->cpu.regs.sp += 2;
        gb->cpu.cycles += 5;
    } else {
        ++gb->cpu.regs.pc;
        gb->cpu.cycles += 2;
    }
}

/* pop DE */
static inline void func_d1(struct gb_s *gb)
{
    gb->cpu.regs.de = mem_read_word(gb, gb->cpu.regs.sp);

    gb->cpu.regs.sp += 2;
    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* jp NC, mem16 */
static inline void func_d2(struct gb_s *gb)
{
    if (!get_flag_c) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp + 1);
        gb->cpu.cycles += 4;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* call NC, mem16 */
static inline void func_d4(struct gb_s *gb)
{
    if (!get_flag_c) {
        gb->cpu.regs.sp -= 2;
        mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);

        gb->cpu.cycles += 6;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* push DE */
static inline void func_d5(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.de);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 4;
}

/* sub A, u8 */
static inline void func_d6(struct gb_s *gb)
{
    uint8_t tmp = mem_read_word(gb, gb->cpu.regs.pc + 1);
    set_flag_c((gb->cpu.regs.a - tmp) < 0);
    set_flag_h(((gb->cpu.regs.a - tmp) & 0xf) > (gb->cpu.regs.a & 0xf));
    gb->cpu.regs.a -= tmp;
    set_flag_n(true);
    set_flag_z(!gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 4;
}

/* rst 10 */
static inline void func_d7(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x10;
    gb->cpu.cycles += 4;
}

/* ret C */
static inline void func_d8(struct gb_s *gb)
{
    if (get_flag_c) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);

        gb->cpu.regs.sp += 2;
        gb->cpu.cycles += 5;
    } else {
        ++gb->cpu.regs.pc;
        gb->cpu.cycles += 2;
    }
}

/* reti */
static inline void func_d9(struct gb_s *gb)
{
    gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp);
    gb->cpu.regs.sp += 2;
    gb->cpu.cycles += 4;

    gb->irq.enabled = true;
    gb->irq.pending = 2;
}

/* jp C, mem16 */
static inline void func_da(struct gb_s *gb)
{
    if (get_flag_c) {
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.sp + 1);
        gb->cpu.cycles += 4;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* call C, mem16 */
static inline void func_dc(struct gb_s *gb)
{
    if (get_flag_c) {
        gb->cpu.regs.sp -= 2;
        mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);
        gb->cpu.regs.pc = mem_read_word(gb, gb->cpu.regs.pc + 1);

        gb->cpu.cycles += 6;
    } else {
        gb->cpu.regs.pc += 3;
        gb->cpu.cycles += 3;
    }
}

/* sbc A, u8 */
static inline void func_de(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    bool tmp_bool = get_flag_c;
    set_flag_h(((tmp & 0xf) + tmp_bool) > (gb->cpu.regs.a & 0xf));
    set_flag_c(tmp + tmp_bool > gb->cpu.regs.a);
    set_flag_n(true);

    gb->cpu.regs.a -= tmp + tmp_bool;

    set_flag_z(!gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rst 18 */
static inline void func_df(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x18;
    gb->cpu.cycles += 4;
}

/* ld (0xff00 + u8), A */
static inline void func_e0(struct gb_s *gb)
{
    uint16_t off = 0xff00u + mem_read_byte(gb, gb->cpu.regs.pc + 1);
    mem_write_byte(gb, off, gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;
}

/* pop HL */
static inline void func_e1(struct gb_s *gb)
{
    gb->cpu.regs.hl = mem_read_word(gb, gb->cpu.regs.sp);

    gb->cpu.regs.sp += 2;
    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* ld (0xff00 + C), A */
static inline void func_e2(struct gb_s *gb)
{
    mem_write_word(gb, 0xff00 + gb->cpu.regs.c, gb->cpu.regs.a);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* push HL */
static inline void func_e5(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.hl);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 4;
}

/* and A, u8 */
static inline void func_e6(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    set_flag_n(false);
    set_flag_h(true);
    set_flag_c(false);

    gb->cpu.regs.a &= tmp;

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rst 20 */
static inline void func_e7(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x20;
    gb->cpu.cycles += 4;
}

/* add SP, u8 */
static inline void func_e8(struct gb_s *gb)
{
    uint32_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    set_flag_z(false);
    set_flag_n(false);
    set_flag_c(((gb->cpu.regs.sp + tmp) & 0xff) < (gb->cpu.regs.sp & 0xff));
    set_flag_c(((gb->cpu.regs.sp + tmp) & 0xf) < (gb->cpu.regs.sp & 0xf));

    gb->cpu.regs.sp += (int8_t) tmp;

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 4;
}

/* jp HL */
static inline void func_e9(struct gb_s *gb)
{
    gb->cpu.regs.pc = gb->cpu.regs.hl;
    ++gb->cpu.cycles;
}

/* ld (mem16), a */
static inline void func_ea(struct gb_s *gb)
{
    uint16_t off = mem_read_word(gb, gb->cpu.regs.pc + 1);
    mem_write_byte(gb, off, gb->cpu.regs.a);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 4;
}

/* xor A, u8 */
static inline void func_ee(struct gb_s *gb)
{
    gb->cpu.regs.a ^= mem_read_byte(gb, gb->cpu.regs.pc + 1);
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* rst 28 */
static inline void func_ef(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x28;
    gb->cpu.cycles += 4;
}

/* ld A, (0xff00 + u8) */
static inline void func_f0(struct gb_s *gb)
{
    uint8_t operand = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    gb->cpu.regs.a = mem_read_byte(gb, 0xff00 + operand);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;
}

/* pop AF */
static inline void func_f1(struct gb_s *gb)
{
    gb->cpu.regs.af = mem_read_word(gb, gb->cpu.regs.sp);

    gb->cpu.regs.sp += 2;
    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 3;
}

/* ld A, (0xff00 + c) */
static inline void func_f2(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_read_byte(gb, 0xff00 + gb->cpu.regs.c);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* di */
static inline void func_f3(struct gb_s *gb)
{
    gb->irq.enabled = false;

    ++gb->cpu.regs.pc;
    ++gb->cpu.cycles;
}

/* push AF */
static inline void func_f5(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.af);

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 4;
}

/* or A, u8 */
static inline void func_f6(struct gb_s *gb)
{
    gb->cpu.regs.a |= mem_read_byte(gb, gb->cpu.regs.pc + 1);
    set_flag_z(!gb->cpu.regs.a);
    set_flag_h(false);
    set_flag_n(false);
    set_flag_c(false);

    gb->cpu.regs.pc = 2;
    gb->cpu.cycles = 2;
}

/* rst 30 */
static inline void func_f7(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc = 0x30;
    gb->cpu.cycles += 4;
}

/* ld HL, SP + u8 */
static inline void func_f8(struct gb_s *gb)
{
    uint32_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);
    set_flag_n(false);
    set_flag_z(false);
    set_flag_c(((gb->cpu.regs.sp + tmp) & 0xff) < (gb->cpu.regs.sp & 0xff));
    set_flag_h(((gb->cpu.regs.sp + tmp) & 0xf) < (gb->cpu.regs.sp & 0xf));

    gb->cpu.regs.hl = gb->cpu.regs.sp + (int8_t) tmp;

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;
}

/* ld SP, HL */
static inline void func_f9(struct gb_s *gb)
{
    gb->cpu.regs.sp = gb->cpu.regs.hl;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* ld A, (mem16) */
static inline void func_fa(struct gb_s *gb)
{
    uint16_t tmp = mem_read_word(gb, gb->cpu.regs.pc + 1);
    gb->cpu.regs.a = mem_read_byte(gb, tmp);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 4;
}

/* ei */
static inline void func_fb(struct gb_s *gb)
{
    gb->irq.enabled = true;
    gb->irq.pending = 2;

    ++gb->cpu.regs.pc;
    gb->cpu.cycles += 2;
}

/* cp a, u8 */
static inline void func_fe(struct gb_s *gb)
{
    uint8_t tmp = mem_read_byte(gb, gb->cpu.regs.pc + 1);

    set_flag_z(gb->cpu.regs.a == tmp);
    set_flag_n(true);
    set_flag_h(((gb->cpu.regs.a - tmp) & 0x0f) > (gb->cpu.regs.a & 0x0f));
    set_flag_c(gb->cpu.regs.a < tmp);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/* rst 38 */
static inline void func_ff(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 1);
    gb->cpu.regs.pc = 0x38;
    gb->cpu.cycles += 2;
}

/*****************************************************************************/

/* The main CPU cyle function */
bool cpu_cycle(struct gb_s *gb)
{
    uint8_t op;

    /* Just increment CPU cycles if CPU is halted */
    if (gb->cpu.halted) {
        ++gb->cpu.cycles;
        return true;
    }

    /* TODO: implement interrupt flushing */
    if (irq_flush(gb))
        gb->cpu.halted = false;

    /* Fetch opcode */
    op = mem_read_byte(gb, gb->cpu.regs.pc);

#ifdef _BOI_DEBUG

    /* Debug verbose */
    debug_print_op(gb, op);

#endif /* !_BOI_DEBUG */

    /* Switch over opcodes and call inline functions (ascending order) */
    switch (op)
    {
        case 0x00:	/* nop */
            func_00(gb);
            break;
        case 0x01:	/* ld BC, u16 */
            func_01(gb);
            break;
        case 0x02:	/* ld (BC), A */
            func_02(gb);
            break;
        case 0x03:	/* inc BC */
            func_03(gb);
            break;
        case 0x04:	/* inc B */
            func_04(gb);
            break;
        case 0x05:	/* dec B */
            func_05(gb);
            break;
        case 0x06:	/* ld B, u8 */
            func_06(gb);
            break;
        case 0x07:	/* rlca */
            func_07(gb);
            break;
        case 0x08:	/* ld (u16), SP */
            func_08(gb);
            break;
        case 0x09:	/* add HL, BC */
            func_09(gb);
            break;
        case 0x0a:	/* ld A, (BC) */
            func_0a(gb);
            break;
        case 0x0b:	/* dec BC */
            func_0b(gb);
            break;
        case 0x0c:	/* inc C */
            func_0c(gb);
            break;
        case 0x0d:	/* dec C */
            func_0d(gb);
            break;
        case 0x0e:	/* ld C, u8 */
            func_0e(gb);
            break;
        case 0x0f:	/* rrca */
            func_0f(gb);
            break;
        case 0x10: /* stop */
            func_10();
            break;
        case 0x11:	/* ld DE, u16 */
            func_11(gb);
            break;
        case 0x12:	/* ld (DE), A */
            func_12(gb);
            break;
        case 0x13:	/* inc DE */
            func_13(gb);
            break;
        case 0x14:	/* inc D */
            func_14(gb);
            break;
        case 0x15:	/* dec D */
            func_15(gb);
            break;
        case 0x16:	/* ld D, u8 */
            func_16(gb);
            break;
        case 0x17:	/* rla */
            func_17(gb);
            break;
        case 0x18:	/* jr rel8 */
            func_18(gb);
            break;
        case 0x19:	/* add HL, DE */
            func_19(gb);
            break;
        case 0x1a:	/* ld A, (DE) */
            func_1a(gb);
            break;
        case 0x1b:	/* dec DE */
            func_1b(gb);
            break;
        case 0x1c:	/* inc E */
            func_1c(gb);
            break;
        case 0x1d:	/* dec E */
            func_1d(gb);
            break;
        case 0x1e:	/* ld E, u8 */
            func_1e(gb);
            break;
        case 0x1f:	/* rr A */
            func_1f(gb);
            break;
        case 0x20:	/* jr NZ, rel8 */
            func_20(gb);
            break;
        case 0x21:	/* ld HL, u16 */
            func_21(gb);
            break;
        case 0x22:	/* ldi (HL), A */
            func_22(gb);
            break;
        case 0x23:	/* inc HL */
            func_23(gb);
            break;
        case 0x24:	/* inc H */
            func_24(gb);
            break;
        case 0x25:	/* dec H */
            func_25(gb);
            break;
        case 0x26:	/* ld H, u8 */
            func_26(gb);
            break;
        case 0x27:	/* daa */
            func_27(gb);
            break;
        case 0x28:	/* jr Z, rel8 */
            func_28(gb);
            break;
        case 0x29:	/* add HL, HL */
            func_29(gb);
            break;
        case 0x2a:	/* ldi A, (HL) */
            func_2a(gb);
            break;
        case 0x2b: 	/* dec HL */
            func_2b(gb);
            break;
        case 0x2c:	/* inc L */
            func_2c(gb);
            break;
        case 0x2d:	/* dec L */
            func_2d(gb);
            break;
        case 0x2e:	/* ld L, u8 */
            func_2e(gb);
            break;
        case 0x2f:	/* cpl */
            func_2f(gb);
            break;
        case 0x30:	/* jr NC, rel8 */
            func_30(gb);
            break;
        case 0x31:	/* ld SP, u16 */
            func_31(gb);
            break;
        case 0x32:	/* ldd (HL), A */
            func_32(gb);
            break;
        case 0x33:	/* inc SP */
            func_33(gb);
            break;
        case 0x34:	/* inc (HL) */
            func_34(gb);
            break;
        case 0x35:	/* dec (HL) */
            func_35(gb);
            break;
        case 0x36:	/* ld (HL), u8 */
            func_36(gb);
            break;
        case 0x37:	/* scf */
            func_37(gb);
            break;
        case 0x38:  /* jr C, rel8 */
            func_38(gb);
            break;
        case 0x39:	/* add HL, SP */
            func_39(gb);
            break;
        case 0x3a:	/* ldd A, (HL) */
            func_3a(gb);
            break;
        case 0x3b:	/* dec SP */
            func_3b(gb);
            break;
        case 0x3c:	/* inc A */
            func_3c(gb);
            break;
        case 0x3d:	/* dec A */
            func_3d(gb);
            break;
        case 0x3e:	/* ld A, u8 */
            func_3e(gb);
            break;
        case 0x3f:	/* ccf */
            func_3f(gb);
            break;
        case 0x40:	/* ld B, B */
            func_40(gb);
            break;
        case 0x41:	/* ld B, C */
            func_41(gb);
            break;
        case 0x42:	/* ld B, D */
            func_42(gb);
            break;
        case 0x43:	/* ld B, E */
            func_43(gb);
            break;
        case 0x44:	/* ld B, H */
            func_44(gb);
            break;
        case 0x45:	/* ld B, L */
            func_45(gb);
            break;
        case 0x46:	/* ld B, (HL) */
            func_46(gb);
            break;
        case 0x47:	/* ld B, A */
            func_47(gb);
            break;
        case 0x48:	/* ld C, B */
            func_48(gb);
            break;
        case 0x49:	/* ld C, C */
            func_49(gb);
            break;
        case 0x4a:	/* ld C, D */
            func_4a(gb);
            break;
        case 0x4b:	/* ld C, E */
            func_4b(gb);
            break;
        case 0x4c:	/* ld C, H */
            func_4c(gb);
            break;
        case 0x4d:	/* ld C, L */
            func_4d(gb);
            break;
        case 0x4e:	/* ld C, (HL) */
            func_4e(gb);
            break;
        case 0x4f:	/* ld C, A */
            func_4f(gb);
            break;
        case 0x50:	/* ld D, B */
            func_50(gb);
            break;
        case 0x51:	/* ld D, C */
            func_51(gb);
            break;
        case 0x52:	/* ld D, D */
            func_52(gb);
            break;
        case 0x53:	/* ld D, E */
            func_53(gb);
            break;
        case 0x54:	/* ld D, H */
            func_54(gb);
            break;
        case 0x55:	/* ld D, L */
            func_55(gb);
            break;
        case 0x56:	/* ld D, (HL) */
            func_56(gb);
            break;
        case 0x57:	/* ld D, A */
            func_57(gb);
            break;
        case 0x58:	/* ld E, B */
            func_58(gb);
            break;
        case 0x59:	/* ld E, C */
            func_59(gb);
            break;
        case 0x5a:	/* ld E, D */
            func_5a(gb);
            break;
        case 0x5b:	/* ld E, E */
            func_5b(gb);
            break;
        case 0x5c:	/* ld E, H */
            func_5c(gb);
            break;
        case 0x5d:	/* ld E, L */
            func_5d(gb);
            break;
        case 0x5e:	/* ld E, (HL) */
            func_5e(gb);
            break;
        case 0x5f:	/* ld E, A */
            func_5f(gb);
            break;
        case 0x60:	/* ld H, B */
            func_60(gb);
            break;
        case 0x61:	/* ld H, C */
            func_61(gb);
            break;
        case 0x62:	/* ld H, D */
            func_62(gb);
            break;
        case 0x63:	/* ld H, E */
            func_63(gb);
            break;
        case 0x64:	/* ld H, H */
            func_64(gb);
            break;
        case 0x65:	/* ld H, L */
            func_65(gb);
            break;
        case 0x66:	/* ld H, (HL) */
            func_66(gb);
            break;
        case 0x67:	/* ld H, A */
            func_67(gb);
            break;
        case 0x68:	/* ld L, B */
            func_68(gb);
            break;
        case 0x69:	/* ld L, C */
            func_69(gb);
            break;
        case 0x6a:	/* ld L, D */
            func_6a(gb);
            break;
        case 0x6b:	/* ld L, E */
            func_6b(gb);
            break;
        case 0x6c:	/* ld L, H */
            func_6c(gb);
            break;
        case 0x6d:	/* ld L, L */
            func_6d(gb);
            break;
        case 0x6e:	/* ld L, (HL) */
            func_6e(gb);
            break;
        case 0x6f:	/* ld L, A */
            func_6f(gb);
            break;
        case 0x70:	/* ld (HL), B */
            func_70(gb);
            break;
        case 0x71:	/* ld (HL), C */
            func_71(gb);
            break;
        case 0x72:	/* ld (HL), D */
            func_72(gb);
            break;
        case 0x73:	/* ld (HL), E */
            func_73(gb);
            break;
        case 0x74:	/* ld (HL), H */
            func_74(gb);
            break;
        case 0x75:	/* ld (HL), L */
            func_75(gb);
            break;
        case 0x76:	/* halt */
            func_76(gb);
            break;
        case 0x77:	/* ld (HL), A */
            func_77(gb);
            break;
        case 0x78:	/* ld A, B */
            func_78(gb);
            break;
        case 0x79:	/* ld A, C */
            func_79(gb);
            break;
        case 0x7a:	/* ld A, D */
            func_7a(gb);
            break;
        case 0x7b:	/* ld A, E */
            func_7b(gb);
            break;
        case 0x7c:	/* ld A, H */
            func_7c(gb);
            break;
        case 0x7d:	/* ld A, L */
            func_7d(gb);
            break;
        case 0x7e:	/* ld A, (HL) */
            func_7e(gb);
            break;
        case 0x7f:	/* ld A, A */
            func_7f(gb);
            break;
        case 0x80:	/* add B */
            func_80(gb);
            break;
        case 0x81:	/* add C */
            func_81(gb);
            break;
        case 0x82:	/* add D */
            func_82(gb);
            break;
        case 0x83:	/* add E */
            func_83(gb);
            break;
        case 0x84:	/* add H */
            func_84(gb);
            break;
        case 0x85:	/* add L */
            func_85(gb);
            break;
        case 0x86:	/* add (HL) */
            func_86(gb);
            break;
        case 0x87:	/* add A */
            func_87(gb);
            break;
        case 0x88:	/* adc B */
            func_88(gb);
            break;
        case 0x89:	/* adc C */
            func_89(gb);
            break;
        case 0x8a:	/* adc D */
            func_8a(gb);
            break;
        case 0x8b:	/* adc E */
            func_8b(gb);
            break;
        case 0x8c:	/* adc H */
            func_8c(gb);
            break;
        case 0x8d:	/* adc L */
            func_8d(gb);
            break;
        case 0x8e:	/* adc (HL) */
            func_8e(gb);
            break;
        case 0x8f:	/* adc A */
            func_8f(gb);
            break;
        case 0x90:	/* sub B */
            func_90(gb);
            break;
        case 0x91:	/* sub C */
            func_91(gb);
            break;
        case 0x92:	/* sub D */
            func_92(gb);
            break;
        case 0x93:	/* sub E */
            func_93(gb);
            break;
        case 0x94:	/* sub H */
            func_94(gb);
            break;
        case 0x95:	/* sub L */
            func_95(gb);
            break;
        case 0x96:	/* sub (HL) */
            func_96(gb);
            break;
        case 0x97:	/* sub A */
            func_97(gb);
            break;
        case 0x98:	/* sbc B */
            func_98(gb);
            break;
        case 0x99:	/* sbc C */
            func_99(gb);
            break;
        case 0x9a:	/* sbc D */
            func_9a(gb);
            break;
        case 0x9b:	/* sbc E */
            func_9b(gb);
            break;
        case 0x9c:	/* sbc H */
            func_9c(gb);
            break;
        case 0x9d:	/* sbc L */
            func_9d(gb);
            break;
        case 0x9e:	/* sbc (HL) */
            func_9e(gb);
            break;
        case 0x9f:	/* sbc A */
            func_9f(gb);
            break;
        case 0xa0:	/* and B */
            func_a0(gb);
            break;
        case 0xa1:	/* and C */
            func_a1(gb);
            break;
        case 0xa2:	/* and D */
            func_a2(gb);
            break;
        case 0xa3:	/* and E */
            func_a3(gb);
            break;
        case 0xa4:	/* and H */
            func_a4(gb);
            break;
        case 0xa5:	/* and L */
            func_a5(gb);
            break;
        case 0xa6:	/* and (HL) */
            func_a6(gb);
            break;
        case 0xa7:	/* and A */
            func_a7(gb);
            break;
        case 0xa8:	/* xor B */
            func_a8(gb);
            break;
        case 0xa9:	/* xor C */
            func_a9(gb);
            break;
        case 0xaa:	/* xor D */
            func_aa(gb);
            break;
        case 0xab:	/* xor E */
            func_ab(gb);
            break;
        case 0xac:	/* xor H */
            func_ac(gb);
            break;
        case 0xad:	/* xor L */
            func_ad(gb);
            break;
        case 0xae:	/* xor (HL) */
            func_ae(gb);
            break;
        case 0xaf:	/* xor A */
            func_af(gb);
            break;
        case 0xb0:	/* or B */
            func_b0(gb);
            break;
        case 0xb1:	/* or C */
            func_b1(gb);
            break;
        case 0xb2:	/* or D */
            func_b2(gb);
            break;
        case 0xb3:	/* or E */
            func_b3(gb);
            break;
        case 0xb4:	/* or H */
            func_b4(gb);
            break;
        case 0xb5:	/* or L */
            func_b5(gb);
            break;
        case 0xb6:	/* or (HL) */
            func_b6(gb);
            break;
        case 0xb7:	/* or A */
            func_b7(gb);
            break;
        case 0xb8:	/* cp B */
            func_b8(gb);
            break;
        case 0xb9:	/* cp C */
            func_b9(gb);
            break;
        case 0xba:	/* cp D */
            func_ba(gb);
            break;
        case 0xbb:	/* cp E */
            func_bb(gb);
            break;
        case 0xbc:	/* cp H */
            func_bc(gb);
            break;
        case 0xbd:	/* cp L */
            func_bd(gb);
            break;
        case 0xbe:	/* cp (HL) */
            func_be(gb);
            break;
        case 0xbf:	/* cp A */
            func_bf(gb);
            break;
        case 0xc0:	/* ret NZ */
            func_c0(gb);
            break;
        case 0xc1:	/* pop BC */
            func_c1(gb);
            break;
        case 0xc2:	/* jp NZ, mem16 */
            func_c2(gb);
            break;
        case 0xc3:	/* jp u16 */
            func_c3(gb);
            break;
        case 0xc4:	/* call NZ, u16 */
            func_c4(gb);
            break;
        case 0xc5:	/* push BC */
            func_c5(gb);
            break;
        case 0xc6:	/* add A, u8 */
            func_c6(gb);
            break;
        case 0xc7:	/* rst 00 */
            func_c7(gb);
            break;
        case 0xc8:	/* ret Z */
            func_c8(gb);
            break;
        case 0xc9:	/* ret */
            func_c9(gb);
            break;
        case 0xca:	/* jp z, mem16 */
            func_ca(gb);
            break;
        case 0xcb: /* CB prefix */
            func_cb(gb);
            break;
        case 0xcc:	/* call Z, u16 */
            func_cc(gb);
            break;
        case 0xcd:	/* call u16 */
            func_cd(gb);
            break;
        case 0xce:	/* adc a, u8 */
            func_ce(gb);
            break;
        case 0xcf:	/* rst 08 */
            func_cf(gb);
            break;
        case 0xd0:	/* ret NC */
            func_d0(gb);
            break;
        case 0xd1:	/* pop DE */
            func_d1(gb);
            break;
        case 0xd2:	/* jp NC, mem16 */
            func_d2(gb);
            break;
        case 0xd3: /* invalid */
            func_invalid(op);
            return false;
        case 0xd4:	/* call NC, mem16 */
            func_d4(gb);
            break;
        case 0xd5:	/* push DE */
            func_d5(gb);
            break;
        case 0xd6:	/* sub A, u8 */
            func_d6(gb);
            break;
        case 0xd7:	/* rst 10 */
            func_d7(gb);
            break;
        case 0xd8:	/* ret C */
            func_d8(gb);
            break;
        case 0xd9:	/* reti */
            func_d9(gb);
            break;
        case 0xda:	/* jp C, mem16 */
            func_da(gb);
            break;
        case 0xdb: /* invalid */
            func_invalid(op);
            return false;
        case 0xdc:	/* call C, mem16 */
            func_dc(gb);
            break;
        case 0xdd: /* invalid */
            func_invalid(op);
            return false;
        case 0xde:	/* sbc A, u8 */
            func_de(gb);
            break;
        case 0xdf:	/* rst 18 */
            func_df(gb);
            break;
        case 0xe0:	/* ld (0xff00 + u8), A */
            func_e0(gb);
            break;
        case 0xe1:	/* pop HL */
            func_e1(gb);
            break;
        case 0xe2:	/* ld (0xff00 + C), A */
            func_e2(gb);
            break;
        case 0xe3: /* invalid */
            func_invalid(op);
            return false;
        case 0xe4: /* invalid */
            func_invalid(op);
            return false;
        case 0xe5:	/* push HL */
            func_e5(gb);
            break;
        case 0xe6:	/* and A, u8 */
            func_e6(gb);
            break;
        case 0xe7:	/* rst 20 */
            func_e7(gb);
            break;
        case 0xe8:	/* add SP, u8 */
            func_e8(gb);
            break;
        case 0xe9:	/* jp HL */
            func_e9(gb);
            break;
        case 0xea:	/* ld (mem16), a */
            func_ea(gb);
            break;
        case 0xeb: /* invalid */
            func_invalid(op);
            return false;
        case 0xec: /* invalid */
            func_invalid(op);
            return false;
        case 0xed: /* invalid */
            func_invalid(op);
            return false;
        case 0xee:	/* xor A, u8 */
            func_ee(gb);
            break;
        case 0xef:	/* rst 28 */
            func_ef(gb);
            break;
        case 0xf0:	/* ld A, (0xff00 + u8) */
            func_f0(gb);
            break;
        case 0xf1:	/* pop AF */
            func_f1(gb);
            break;
        case 0xf2:	/* ld A, (0xff00 + c) */
            func_f2(gb);
            break;
        case 0xf3:	/* di */
            func_f3(gb);
            break;
        case 0xf4: /* invalid */
            func_invalid(op);
            return false;
        case 0xf5:	/* push AF */
            func_f5(gb);
            break;
        case 0xf6:	/* or A, u8 */
            func_f6(gb);
            break;
        case 0xf7:	/* rst 30 */
            func_f7(gb);
            break;
        case 0xf8:	/* ld HL, SP + u8 */
            func_f8(gb);
            break;
        case 0xf9:	/* ld SP, HL */
            func_f9(gb);
            break;
        case 0xfa:	/* ld A, (mem16) */
            func_fa(gb);
            break;
        case 0xfb:	/* ei */
            func_fb(gb);
            break;
        case 0xfc: /* invalid */
            func_invalid(op);
            return false;
        case 0xfd: /* invalid */
            func_invalid(op);
            return false;
        case 0xfe:	/* cp a, u8 */
            func_fe(gb);
            break;
        case 0xff:	/* rst 38 */
            func_ff(gb);
            break;
        default: /* We should never get here */
            func_invalid(op);
            return false;
    }

    return true;
}
