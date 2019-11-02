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

    /* Interrupts are enabled */
    bool irq;

    /* Interrupts should be enabled after next instruction */
    bool irq_next;

    /* Pending interrupt */
    uint8_t irq_pending;

    /* System is halted */
    bool halted;

    /* Number of cycles for the current instruction */
    uint8_t cycles;
};

/*
 *****************************************************************************/

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
 * The actual GameBoy structure
 */
struct gb_s {
    struct cpu_s cpu;
    struct rom_s rom;
    uint8_t *mem;
};

/*****************************************************************************/

#endif /* !BOI_GB_H */
