#include <stdbool.h>
#include <stdio.h>

#include "gb.h"
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

    /* Unset all flags */
    gb->cpu.flags.z = false;
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
    gb->cpu.flags.c = false;

    /* Enable interrupts and set an interrupt for next instruction */
    gb->cpu.irq = true;
    gb->cpu.irq_next = true;

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

static void func_rlc(struct gb_s *gb, uint8_t reg)
{
    uint8_t old;
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            old = gb->cpu.regs.b >> 7;
            gb->cpu.regs.b = gb->cpu.regs.b << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.b;
            break;
        case 0x01: /* C */
            old = gb->cpu.regs.c >> 7;
            gb->cpu.regs.c = gb->cpu.regs.c << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.c;
            break;
        case 0x02: /* D */
            old = gb->cpu.regs.d >> 7;
            gb->cpu.regs.d = gb->cpu.regs.d << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.d;
            break;
        case 0x03: /* E */
            old = gb->cpu.regs.e >> 7;
            gb->cpu.regs.e = gb->cpu.regs.e << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.e;
            break;
        case 0x04: /* H */
            old = gb->cpu.regs.h >> 7;
            gb->cpu.regs.h = gb->cpu.regs.h << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.h;
            break;
        case 0x05: /* L */
            old = gb->cpu.regs.l >> 7;
            gb->cpu.regs.l = gb->cpu.regs.l << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.l;
            break;
        case 0x06: /* (HL) */
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            old = tmp >> 7;
            tmp = tmp << 1 | old;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.flags.z = !tmp;
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            old = gb->cpu.regs.a >> 7;
            gb->cpu.regs.a = gb->cpu.regs.a << 1 | old;
            gb->cpu.flags.z = !gb->cpu.regs.a;
            break;
    }
    gb->cpu.flags.c = old;
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
}

static void func_rrc(struct gb_s *gb, uint8_t reg)
{
    uint8_t old;
    uint8_t tmp;

    switch(reg) {
        case 0x00: /* B */
            old = gb->cpu.regs.b & 0x1;
            gb->cpu.regs.b = gb->cpu.regs.b >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.b;
            break;
        case 0x01: /* C */
            old = gb->cpu.regs.c & 0x1;
            gb->cpu.regs.c = gb->cpu.regs.c >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.c;
            break;
        case 0x02: /* D */
            old = gb->cpu.regs.d & 0x1;
            gb->cpu.regs.d = gb->cpu.regs.d >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.d;
            break;
        case 0x03: /* E */
            old = gb->cpu.regs.e & 0x1;
            gb->cpu.regs.e = gb->cpu.regs.e >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.e;
            break;
        case 0x04: /* H */
            old = gb->cpu.regs.h & 0x1;
            gb->cpu.regs.h = gb->cpu.regs.h >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.h;
            break;
        case 0x05: /* L */
            old = gb->cpu.regs.l & 0x1;
            gb->cpu.regs.l = gb->cpu.regs.l >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.l;
            break;
        case 0x06: /* (HL) */
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            old = tmp & 0x1;
            tmp = tmp >> 1 | old << 7;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.flags.z = !tmp;
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            old = gb->cpu.regs.a & 0x1;
            gb->cpu.regs.a = gb->cpu.regs.a >> 1 | old << 7;
            gb->cpu.flags.z = !gb->cpu.regs.a;
            break;
    }
    gb->cpu.flags.c = old;
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
}

static void func_rl(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;
    bool tmp_c = gb->cpu.flags.c;

    switch(reg) {
        case 0x00: /* B */
            gb->cpu.flags.c = gb->cpu.regs.b >> 7;
            gb->cpu.regs.b = gb->cpu.regs.b << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.b;
            break;
        case 0x01: /* C */
            gb->cpu.flags.c = gb->cpu.regs.c >> 7;
            gb->cpu.regs.c = gb->cpu.regs.c << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.c;
            break;
        case 0x02: /* D */
            gb->cpu.flags.c = gb->cpu.regs.d >> 7;
            gb->cpu.regs.d = gb->cpu.regs.d << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.d;
            break;
        case 0x03: /* E */
            gb->cpu.flags.c = gb->cpu.regs.e >> 7;
            gb->cpu.regs.e = gb->cpu.regs.e << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.e;
            break;
        case 0x04: /* H */
            gb->cpu.flags.c = gb->cpu.regs.h >> 7;
            gb->cpu.regs.h = gb->cpu.regs.h << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.h;
            break;
        case 0x05: /* L */
            gb->cpu.flags.c = gb->cpu.regs.l >> 7;
            gb->cpu.regs.l = gb->cpu.regs.l << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.l;
            break;
        case 0x06: /* (HL) */
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            gb->cpu.flags.c = tmp >> 7;
            tmp = tmp << 1 | tmp_c;
            gb->cpu.flags.z = !tmp;
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.flags.c = gb->cpu.regs.a >> 7;
            gb->cpu.regs.a = gb->cpu.regs.a << 1 | tmp_c;
            gb->cpu.flags.z = !gb->cpu.regs.a;
            break;
    }
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
}

static void func_rr(struct gb_s *gb, uint8_t reg)
{
    uint8_t tmp;
    bool tmp_c = gb->cpu.flags.c;

    switch(reg) {
        case 0x00: /* B */
            gb->cpu.flags.c = gb->cpu.regs.b & 0x1;
            gb->cpu.regs.b = gb->cpu.regs.b >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.b;
            break;
        case 0x01: /* C */
            gb->cpu.flags.c = gb->cpu.regs.c & 0x1;
            gb->cpu.regs.c = gb->cpu.regs.c >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.c;
            break;
        case 0x02: /* D */
            gb->cpu.flags.c = gb->cpu.regs.d & 0x1;
            gb->cpu.regs.d = gb->cpu.regs.d >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.d;
            break;
        case 0x03: /* E */
            gb->cpu.flags.c = gb->cpu.regs.e & 0x1;
            gb->cpu.regs.e = gb->cpu.regs.e >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.e;
            break;
        case 0x04: /* H */
            gb->cpu.flags.c = gb->cpu.regs.h & 0x1;
            gb->cpu.regs.h = gb->cpu.regs.h >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.h;
            break;
        case 0x05: /* L */
            gb->cpu.flags.c = gb->cpu.regs.l & 0x1;
            gb->cpu.regs.l = gb->cpu.regs.l >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.l;
            break;
        case 0x06: /* (HL) */
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            gb->cpu.flags.c = tmp & 0x1;
            tmp = tmp >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !tmp;
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.flags.c = gb->cpu.regs.a & 0x1;
            gb->cpu.regs.a = gb->cpu.regs.a >> 1 | tmp_c << 7;;
            gb->cpu.flags.z = !gb->cpu.regs.a;
            break;
    }
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
}

static void func_sla(struct gb_s *gb, uint8_t reg)
{
    switch(reg) {
        case 0x00: /* B */
            break;
        case 0x01: /* C */
            break;
        case 0x02: /* D */
            break;
        case 0x03: /* E */
            break;
        case 0x04: /* H */
            break;
        case 0x05: /* L */
            break;
        case 0x06: /* (HL) */
            break;
        case 0x07: /* A */
            break;
    }
}

static void func_sra(struct gb_s *gb, uint8_t reg)
{
    switch(reg) {
        case 0x00: /* B */
            break;
        case 0x01: /* C */
            break;
        case 0x02: /* D */
            break;
        case 0x03: /* E */
            break;
        case 0x04: /* H */
            break;
        case 0x05: /* L */
            break;
        case 0x06: /* (HL) */
            break;
        case 0x07: /* A */
            break;
    }
}

static void func_swap(struct gb_s *gb, uint8_t reg)
{
    switch(reg) {
        case 0x00: /* B */
            break;
        case 0x01: /* C */
            break;
        case 0x02: /* D */
            break;
        case 0x03: /* E */
            break;
        case 0x04: /* H */
            break;
        case 0x05: /* L */
            break;
        case 0x06: /* (HL) */
            break;
        case 0x07: /* A */
            break;
    }
}

static void func_srl(struct gb_s *gb, uint8_t reg)
{
    switch(reg) {
        case 0x00: /* B */
            break;
        case 0x01: /* C */
            break;
        case 0x02: /* D */
            break;
        case 0x03: /* E */
            break;
        case 0x04: /* H */
            break;
        case 0x05: /* L */
            break;
        case 0x06: /* (HL) */
            break;
        case 0x07: /* A */
            break;
    }
}

static void func_bit(struct gb_s *gb, uint8_t reg, uint8_t mask)
{
    switch(reg) {
        case 0x00: /* B */
            gb->cpu.flags.z = !(gb->cpu.regs.b & mask);
            break;
        case 0x01: /* C */
            gb->cpu.flags.z = !(gb->cpu.regs.c & mask);
            break;
        case 0x02: /* D */
            gb->cpu.flags.z = !(gb->cpu.regs.d & mask);
            break;
        case 0x03: /* E */
            gb->cpu.flags.z = !(gb->cpu.regs.e & mask);
            break;
        case 0x04: /* H */
            gb->cpu.flags.z = !(gb->cpu.regs.h & mask);
            break;
        case 0x05: /* L */
            gb->cpu.flags.z = !(gb->cpu.regs.l & mask);
            break;
        case 0x06: /* (HL) */
            gb->cpu.flags.z = !(mem_get_byte(gb, gb->cpu.regs.hl) & mask);
            gb->cpu.cycles += 1;
            break;
        case 0x07: /* A */
            gb->cpu.flags.z = !(gb->cpu.regs.a & mask);
            break;
    }
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = true;
}

static void func_res(struct gb_s *gb, uint8_t reg, uint8_t mask)
{
    uint8_t tmp;
    switch(reg) {
        case 0x00: /* B */
            gb->cpu.regs.b &= ~mask;
            break;
        case 0x01: /* C */
            gb->cpu.regs.c &= ~mask;
            break;
        case 0x02: /* D */
            gb->cpu.regs.d &= ~mask;
            break;
        case 0x03: /* E */
            gb->cpu.regs.e &= ~mask;
            break;
        case 0x04: /* H */
            gb->cpu.regs.h &= ~mask;
            break;
        case 0x05: /* L */
            gb->cpu.regs.l &= ~mask;
            break;
        case 0x06: /* (HL) */
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            tmp &= ~mask;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.regs.a &= ~mask;
            break;
    }
}

static void func_set(struct gb_s *gb, uint8_t reg, uint8_t mask)
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
            tmp = mem_get_byte(gb, gb->cpu.regs.hl);
            tmp |= mask;
            mem_write_byte(gb, gb->cpu.regs.hl, tmp);
            gb->cpu.cycles += 2;
            break;
        case 0x07: /* A */
            gb->cpu.regs.a |= mask;
            break;
    }
}

static void (*const cb_single_ops[CB_SINGLE_OP_COUNT])
    (struct gb_s*, uint8_t) = {

        func_rlc,
        func_rrc,
        func_rl,
        func_rr,
        func_sla,
        func_sra,
        func_swap,
        func_srl
    };

static void (*const cb_double_ops[CB_DOUBLE_OP_COUNT])
    (struct gb_s *, uint8_t, uint8_t) = {

        func_bit,
        func_res,
        func_set
    };

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

static inline void func_not_implemented(struct gb_s *gb, uint8_t op)
{
    printf("Unhandled opcode: 0x%02x\n", op);
    gb->cpu.regs.pc += 1;

}

static inline void func_invalid(uint8_t op)
{
    fprintf(stderr, "Error: invalid opcode:  0x%02x\n", op);

}

static inline void func_00(struct gb_s *gb)
{
    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 1;

}

static inline void func_02(struct gb_s *gb)
{
    mem_write_byte(gb, gb->cpu.regs.bc, gb->cpu.regs.a);

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 2;

}

static inline void func_18(struct gb_s *gb)
{

    gb->cpu.cycles += 3;
    gb->cpu.regs.pc += (int8_t) mem_get_byte(gb, gb->mem[gb->cpu.regs.sp + 1])
        + 2;

}

static inline void func_28(struct gb_s *gb)
{
    if (gb->cpu.flags.z) {
        /* TODO: check the +2 here is right skipping operands */
        gb->cpu.regs.pc += (int8_t) mem_get_byte(gb,
                gb->mem[gb->cpu.regs.sp + 1]) + 2;
        gb->cpu.cycles += 3;
    } else {
        gb->cpu.regs.pc += 2;
        gb->cpu.cycles += 2;
    }

}

static inline void func_3e(struct gb_s *gb)
{
    gb->cpu.regs.a = mem_get_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;

}

static inline void func_47(struct gb_s *gb)
{
    gb->cpu.regs.b = gb->cpu.regs.a;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 1;

}

static inline void func_c3(struct gb_s *gb)
{
    /* TODO: check we are not out of bounds */
    gb->cpu.regs.pc = mem_get_word(gb, gb->cpu.regs.pc + 1);
    gb->cpu.cycles += 4;

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
    gb->cpu.regs.sp += 2;
    gb->cpu.cycles += 2;

    op = gb->mem[gb->cpu.regs.pc + 1];

    /* Get register and check if it is a single operand opcode */
    reg = op & 0x07;
    op >>= 3;

    /* It is, call function and return */
    if (op < 0x08) {
        cb_single_ops[op](gb, reg);
        return;
    }

    /* It's a double operand opcode, decode bit index and call function */
    bit = op & 0x0f;
    op >>= 3;

    /*
     * An opcode id is always between 1 and 3 so op - 1 is the index.
     * 1 << bit creates the mask for the bit operation.
     */
    cb_double_ops[op - 1](gb, reg, 1 << bit);
}

static inline void func_cd(struct gb_s *gb)
{
    gb->cpu.regs.sp -= 2;

    /* Skip the current instr and it's two byte operand and push next instr */
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc + 3);

    gb->cpu.regs.pc = mem_get_byte(gb, gb->cpu.regs.pc + 1);

    gb->cpu.cycles += 6;

}

static inline void func_af(struct gb_s *gb)
{
    gb->cpu.regs.a = 0;

    gb->cpu.flags.z = true;
    gb->cpu.flags.n = false;
    gb->cpu.flags.h = false;
    gb->cpu.flags.c = false;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 1;

}

static inline void func_e0(struct gb_s *gb)
{
    uint16_t off = 0xff00u + mem_get_byte(gb, gb->cpu.regs.pc + 1);
    mem_write_byte(gb, off, gb->cpu.regs.a);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;

}

static inline void func_ea(struct gb_s *gb)
{
    uint16_t off = mem_get_word(gb, gb->cpu.regs.pc + 1);
    mem_write_byte(gb, off, gb->cpu.regs.a);

    gb->cpu.regs.pc += 3;
    gb->cpu.cycles += 4;

}

static inline void func_f0(struct gb_s *gb)
{
    uint8_t operand = mem_get_byte(gb, gb->cpu.regs.sp + 1);
    gb->cpu.regs.a = mem_get_byte(gb, 0xff00u + operand);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 3;

}

static inline void func_f3(struct gb_s *gb)
{
    gb->cpu.irq = false;

    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 1;

}

static inline void func_fe(struct gb_s *gb)
{
    uint8_t tmp = mem_get_byte(gb, gb->cpu.regs.pc + 1);
    uint8_t a = gb->cpu.regs.a;

    gb->cpu.flags.z = (a == tmp);
    gb->cpu.flags.n = true;
    gb->cpu.flags.h = (((a - tmp) & 0x0f) > (a & 0x0f));
    gb->cpu.flags.c = (a < tmp);

    gb->cpu.regs.pc += 2;
    gb->cpu.cycles += 2;
}

/*****************************************************************************/

bool cpu_cycle(struct gb_s *gb)
{
    uint8_t op;

    /* Just increment CPU cycles if CPU is halted */
    if (gb->cpu.halted) {
        ++gb->cpu.cycles;
        return true;
    }

    /* TODO: implement interrupt flushing */

    /* Fetch opcode */
    op = mem_get_byte(gb, gb->cpu.regs.pc);

#ifdef _BOI_DEBUG

    /* Debug verbose */
    debug_print_op(gb, op);

#endif /* !_BOI_DEBUG */

    /* Switch over opcodes and call inline functions (ascending order) */
    switch (op) {
        case 0x00: /* nop */
            func_00(gb);
            break;
        case 0x02: /* ld (BC), A */
            func_02(gb);
            break;
        case 0x18: /* jr i8 */
            func_18(gb);
            break;
        case 0x28: /* jr Z, i8 */
            func_28(gb);
            break;
        case 0x3e: /* ld A, u8 */
            func_3e(gb);
            break;
        case 0x47: /* ld, B, A */
            func_47(gb);
            break;
        case 0xaf: /* xor A, A */
            func_af(gb);
            break;
        case 0xc3: /* jp u16 */
            func_c3(gb);
            break;
        case 0xcb: /* cb prefix */
            func_cb(gb);
            break;
        case 0xcd: /* call u16 */
            func_cd(gb);
            break;
        case 0xd3: /* invalid */
            func_invalid(op);
            return false;
        case 0xdb: /* invalid */
            func_invalid(op);
            return false;
        case 0xdd: /* invalid */
            func_invalid(op);
            return false;
        case 0xe0: /* ld (0xff00 + u8), A */
            func_e0(gb);
            break;
        case 0xe3: /* invalid */
            func_invalid(op);
            return false;
        case 0xe4: /* invalid */
            func_invalid(op);
            return false;
        case 0xeb: /* invalid */
            func_invalid(op);
            return false;
        case 0xec: /* invalid */
            func_invalid(op);
            return false;
        case 0xed: /* invalid */
            func_invalid(op);
            return false;
        case 0xea: /* ld (u16), A */
            func_ea(gb);
            break;
        case 0xf0: /* ld A, (0xff00 + u8) */
            func_f0(gb);
            break;
        case 0xf3: /* di */
            func_f3(gb);
            break;
        case 0xf4: /* invalid */
            func_invalid(op);
            return false;
        case 0xfc: /* invalid */
            func_invalid(op);
            return false;
        case 0xfd: /* invalid */
            func_invalid(op);
            return false;
        case 0xfe: /* cp A, u8 */
            func_fe(gb);
            break;
        default: /* We haven't implemented this opcode yet */
            func_not_implemented(gb, op);
            return false;
    }

    return true;
}
