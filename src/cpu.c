#include <stdbool.h>

#include "gb.h"

/* Initialize CPU to default values */
void cpu_init(struct gb_s *gb) {

    /* Set all registers to 0 */
    gb->cpu.regs.af = 0;
    gb->cpu.regs.bc = 0;
    gb->cpu.regs.de = 0;
    gb->cpu.regs.hl = 0;
    gb->cpu.regs.sp = 0;
    gb->cpu.regs.pc = 0;

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

    return;
}
