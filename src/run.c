#include <stdbool.h>
#include <stdio.h>

#include "gb.h"
#include "ops.h"

bool run(struct gb_s *gb)
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
