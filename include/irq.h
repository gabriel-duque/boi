#ifndef BOI_IRQ_H
#define BOI_IRQ_H

#include <stdbool.h>

void irq_init(struct gb_s *gb);
bool irq_flush(struct gb_s *gb);

#endif /* !BOI_IRQ_H */
