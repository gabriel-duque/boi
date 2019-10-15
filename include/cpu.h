#ifndef BOI_CPU_H
#define BOI_CPU_H

#include <stdbool.h>

#include "gb.h"

void cpu_init(struct gb_s *gb);

bool cpu_cycle(struct gb_s *gb);

#endif /* !BOI_CPU_H */
