#ifdef _BOI_DEBUG
#include <assert.h>
#include <stddef.h>
#endif /* !_BOI_DEBUG */

#include <stdbool.h>

#include "cpu.h"

/* Initialize CPU to default values */
void cpu_init(struct cpu_s *cpu) {

#ifdef _BOI_DEBUG
    assert(cpu != NULL);
#endif /* !_BOI_DEBUG */

    /* Set all registers to 0 */
    cpu->regs.af = 0;
    cpu->regs.bc = 0;
    cpu->regs.de = 0;
    cpu->regs.hl = 0;
    cpu->regs.sp = 0;
    cpu->regs.pc = 0;

    /* Unset all flags */
    cpu->flags.z = false;
    cpu->flags.n = false;
    cpu->flags.h = false;
    cpu->flags.c = false;

    /* Enable interrupts and set an interrupt for next instruction */
    cpu->irq = true;
    cpu->irq_next = true;

    /* We start in non-halted mode */
    cpu->halted = false;

    /* Although this will alredy be reset we do it out of convention when
     * setting all the fields in a structure
     */
    cpu->cycles = 0;

    return;
}
