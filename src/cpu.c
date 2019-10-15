#include <stdbool.h>
#include <stdio.h>

#include "gb.h"
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

bool cpu_cycle(struct gb_s *gb)
{
    struct op_s opcode;
    bool ret;
    uint8_t op = gb->mem[gb->cpu.regs.pc];

    for (uint16_t i = 0; i < OPCODE_COUNT; ++i) {
        if (opcodes[i].op == op) {
            opcode = opcodes[i];
            break;
        }
    }

#ifdef _BOI_DEBUG
    printf("0x%04x: 0x%02x: %s\n", gb->cpu.regs.pc, opcode.op, opcode.name);
#endif /* !_BOI_DEBUG */

    ret = opcode.func(gb);
    gb->cpu.regs.pc += opcode.size;

    return ret;
}
