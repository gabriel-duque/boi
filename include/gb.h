/* This header defines all the types used in Boi */

#ifndef BOI_GB_H
#define BOI_GB_H

#include <stdbool.h>
#include <stdint.h>

/* To avoid unused variable error */
#define UNUSED(expr) do { (void)(expr); } while (0)

/* Macros to access flag bit values individually */
#define set_flag_z(x) (gb->cpu.regs.f = (gb->cpu.regs.f & 0x7f) | ((x) << 7))
#define set_flag_n(x) (gb->cpu.regs.f = (gb->cpu.regs.f & 0xbf) | ((x) << 6))
#define set_flag_h(x) (gb->cpu.regs.f = (gb->cpu.regs.f & 0xdf) | ((x) << 5))
#define set_flag_c(x) (gb->cpu.regs.f = (gb->cpu.regs.f & 0xef) | ((x) << 4))

#define get_flag_z !!((gb->cpu.regs.f & 0x80))
#define get_flag_n !!((gb->cpu.regs.f & 0x40))
#define get_flag_h !!((gb->cpu.regs.f & 0x20))
#define get_flag_c !!((gb->cpu.regs.f & 0x10))

/******************************************************************************
 * CPU related types
 */

/* CPU registers */
struct regs_s {
    union {
        struct {
            /* f is the flag register */
            uint8_t f;
            uint8_t a;
        };
        uint16_t af;
    };

    union {
        struct {
            uint8_t c;
            uint8_t b;
        };
        uint16_t bc;
    };

    union {
        struct {
            uint8_t e;
            uint8_t d;
        };
        uint16_t de;
    };

    union {
        struct {
            uint8_t l;
            uint8_t h;
        };
        uint16_t hl;
    };

    uint16_t sp;
    uint16_t pc;
};

/* The actual CPU structure */
struct cpu_s {

    /* Registers */
    struct regs_s regs;

    /* System is halted */
    bool halted;

    /* Number of cycles for the current instruction */
    uint8_t cycles;
};

/*
 *****************************************************************************/

/******************************************************************************
 * Interrupt related types
 */

struct irq_s {

    /* Interrupts are enabled */
    bool enabled;

    /* Pending interrupt */
    uint8_t pending;

    /* Interrupt flags */
    bool vblank;
    bool lcd;
    bool clk;
    bool serial;
    bool joypad;

    /* Interrupt masks */
    bool vblank_msk;
    bool lcd_msk;
    bool clk_msk;
    bool serial_msk;
    bool joypad_msk;
};

/*****************************************************************************/

/******************************************************************************
 * ROM related types
 */

/* Cartridge types */
enum cartridge_type_e {
    ROM,
    MBC1,
    MBC2,
    MMM01,
    MBC3,
    MBC5
};

/* Structure to get cartridge info when parsing GameBoy header */
struct cartridge_s {
    uint8_t id;
    enum cartridge_type_e type;
    char *name;
};

/* Actual ROM structure */
struct rom_s {
    uint8_t *raw;
    enum cartridge_type_e type;
};

/*****************************************************************************/

/******************************************************************************
 * The memory structure
 */

struct mem_s {
    uint8_t *raw;
    uint8_t dma_pending;
};

/*****************************************************************************/

/******************************************************************************
 * The actual GameBoy structure
 */
struct gb_s {
    struct cpu_s cpu;
    struct rom_s rom;
    struct mem_s mem;
    struct irq_s irq;
};

/*****************************************************************************/

#endif /* !BOI_GB_H */
