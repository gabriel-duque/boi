/* This header defines all the types used in Boi */

#ifndef BOI_GB_H
#define BOI_GB_H

#include <stdbool.h>
#include <stdint.h>

/* To avoid unused variable error */
#define UNUSED(expr) do { (void)(expr); } while (0)

/******************************************************************************
 * CPU related types
 */

/* CPU registers */
struct regs_s {
    union {
        struct {
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

/* Flags register */
struct flags_s {

    /*
     * Zero: set if the result of a math operation is zero or two values become
     * equal
     */
    bool z;

    /*
     * Substract flag: set if the last math operation performed a
     * substraction
     */
    bool n;

    /*
     * Half carry flag: set if a carry occurred from the lower nibble in the
     * last math operation
     */
    bool h;

    /*
     * Carry: set if a carry occured from the lower nibble in the last math
     * operation.
     */
    bool c;

};

/* The actual CPU structure */
struct cpu_s {

    /* Registers */
    struct regs_s regs;

    /* Flags */
    struct flags_s flags;

    /* Interrupts are enabled */
    bool irq;

    /* Interrupts should be enabled after next instruction */
    bool irq_next;

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

/******************************************************************************
 * Opcodes
 */

struct op_s {
    uint8_t op;
    char *name;
    bool (*func) (struct gb_s*, uint8_t);
    uint8_t size;
};

/*****************************************************************************/

#endif /* !BOI_GB_H */
