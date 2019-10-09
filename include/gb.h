/* This header defines all the types used in Boi */

#ifndef BOI_GB_H
#define BOI_GB_H

#include <stdbool.h>
#include <stdint.h>

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

/* The while GameBoy struture */
struct gb_s {
    struct cpu_s cpu;
};

#endif /* !BOI_GB_H */
