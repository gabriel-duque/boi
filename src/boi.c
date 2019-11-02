#include <stdio.h>
#include <stdlib.h>

#include "clk.h"
#include "cpu.h"
#include "gb.h"
#include "gpu.h"
#include "irq.h"
#include "mem.h"
#include "rom.h"

/* Main entry point for the Boi emulator */
int main(int argc, char **argv)
{
    const char *filename;

    struct gb_s gb;

    /* Handle no file given or to many files given */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <rom-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    filename = argv[1];

    printf("%s\n", "Welcome to the Boi GameBoy emulator!");

#ifdef _BOI_DEBUG
    printf("The emulator has been built for debugging...\n");
#endif /* !_BOI_DEBUG */

    printf("Attempting to load ROM: %s...\n", filename);

    /* Initialize the GameBoy system */
    rom_load(&gb, filename);
    mem_init(&gb);
    cpu_init(&gb);
    irq_init(&gb);

    /* Loop and execute instructions */
    while (cpu_cycle(&gb) && gpu_cycle(&gb))
        clk_tick(&gb);

    /* TODO: cleanup */
}
