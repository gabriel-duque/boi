#include <stdbool.h>

#include "gb.h"

bool irq_flush(struct gb_s *gb)
{
    if (gb->irq.pending == 2) {
        --gb->irq.pending;
        return false;
    }

    gb->irq.pending = 0;
    return false;
}
