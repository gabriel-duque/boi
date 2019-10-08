#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

int main(int argc, char **argv) {
    char *filename;
    struct cpu_s cpu;

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

    //if (load_rom(filename)) {
    //    fprintf(stderr, "An error occured while load the ROM...\n");
    //    exit(EXIT_FAILURE);
    //}
    printf("ROM succesfully loaded...\n");

    cpu_init(&cpu);
}
