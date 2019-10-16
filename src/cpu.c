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
 * These are all the inline functions called in the *big* switch later
 */

static inline bool func_not_implemented(struct gb_s *gb, uint8_t op)
{
    printf("Unhandled opcode: 0x%02x\n", op);
    gb->cpu.regs.pc += 1;
    return true;
}

static inline bool func_invalid(uint8_t op)
{
    fprintf(stderr, "Error: invalid opcode:  0x%02x\n", op);
    return false;
}

static inline bool func_nop(struct gb_s *gb)
{
    gb->cpu.regs.pc += 1;
    gb->cpu.cycles += 1;
    return true;
}

static inline bool func_c3(struct gb_s *gb)
{
    /* TODO: check we are not out of bounds */
    gb->cpu.regs.pc = mem_get_word(gb, gb->cpu.regs.pc + 1);
    gb->cpu.cycles += 4;
    return true;
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
            return func_nop(gb);
            break;
        case 0xc3: /* 0xc3: jp u16 */
            return func_c3(gb);
        case 0xd3: /* Invalid */
            return func_invalid(op);
            break;
        case 0xdb: /* Invalid */
            return func_invalid(op);
            break;
        case 0xdd: /* Invalid */
            return func_invalid(op);
            break;
        case 0xe3: /* Invalid */
            return func_invalid(op);
            break;
        case 0xe4: /* Invalid */
            return func_invalid(op);
            break;
        case 0xeb: /* Invalid */
            return func_invalid(op);
            break;
        case 0xec: /* Invalid */
            return func_invalid(op);
            break;
        case 0xed: /* Invalid */
            return func_invalid(op);
            break;
        case 0xf4: /* Invalid */
            return func_invalid(op);
            break;
        case 0xfc: /* Invalid */
            return func_invalid(op);
            break;
        case 0xfd: /* Invalid */
            return func_invalid(op);
            break;
        default: /* We haven't implemented this opcode yet */
            return func_not_implemented(gb, op);
            break;
    }
}
