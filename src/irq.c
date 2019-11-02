#include <stdbool.h>
#include <stdint.h>

#include "gb.h"
#include "mem.h"

#define VBLANK_VECT 0x40
#define LCD_VECT    0x48
#define CLK_VECT    0x50
#define SERIAL_VECT 0x58
#define JOYPAD_VECT 0x60

void irq_init(struct gb_s *gb)
{
    gb->irq.enabled = 0;
    gb->irq.pending = 0;

    gb->irq.vblank = 0;
    gb->irq.lcd = 0;
    gb->irq.clk = 0;
    gb->irq.serial = 0;
    gb->irq.joypad = 0;

    gb->irq.vblank_msk = 1;
    gb->irq.lcd_msk = 1;
    gb->irq.clk_msk = 1;
    gb->irq.serial_msk = 1;
    gb->irq.joypad_msk = 1;
}

static inline void irq(struct gb_s *gb, uint8_t vect)
{
    gb->irq.vblank = 0;
    gb->irq.enabled = false;

    gb->cpu.halted = false;
    gb->cpu.regs.sp -= 2;
    mem_write_word(gb, gb->cpu.regs.sp, gb->cpu.regs.pc);
    gb->cpu.regs.pc = vect;
}

bool irq_flush(struct gb_s *gb)
{
    /* Flush highest priority interrupt */
    if (gb->irq.pending == 2) {
        --gb->irq.pending;
        return false;
    }

    gb->irq.pending = 0;

    if (!gb->irq.enabled && (
                (gb->irq.vblank && !gb->irq.vblank_msk)
                || (gb->irq.lcd && !gb->irq.lcd_msk)
                || (gb->irq.clk && !gb->irq.clk_msk)
                || (gb->irq.serial && !gb->irq.serial_msk)
                || (gb->irq.joypad && !gb->irq.joypad_msk)
                )
       )
        return true;

    if (gb->irq.vblank && !gb->irq.vblank_msk)
        irq(gb, VBLANK_VECT);
    else if (gb->irq.lcd && !gb->irq.lcd_msk)
        irq(gb, LCD_VECT);
    else if (gb->irq.clk && !gb->irq.clk_msk)
        irq(gb, CLK_VECT);
    else if (gb->irq.serial && !gb->irq.serial_msk)
        irq(gb, SERIAL_VECT);
    else if (gb->irq.joypad && !gb->irq.joypad_msk)
        irq(gb, JOYPAD_VECT);

    return false;
}
