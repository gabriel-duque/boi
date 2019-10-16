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
 * These are all the static inline functions called in the *big* switch later.
 *
 * For the sake of simplicity there is one function for unhandled opcodes,
 * one for invalid opcodes and then one function per opcode.
 *
 * All the opcode functions are named:
 *      func_xx
 *
 * where xx is the hex representation of the opcode.
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

static inline void func_cb(struct gb_s *gb)
{
    /* TODO: handle CB prefix */
    (void) gb;
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
            break;
    }

    return true;
}
