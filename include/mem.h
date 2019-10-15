#ifndef BOI_MEM_H
#define BOI_MEM_H

#include <stdint.h>

#include "gb.h"

void mem_init(struct gb_s *gb);

uint8_t  mem_get_byte(struct gb_s *gb, uint16_t off);
uint16_t mem_get_word(struct gb_s *gb, uint16_t off);

#endif /* !BOI_MEM_H */
