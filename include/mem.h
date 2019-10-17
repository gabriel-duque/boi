#ifndef BOI_MEM_H
#define BOI_MEM_H

#include <stdint.h>

#include "gb.h"

void mem_init(struct gb_s *gb);

uint8_t  mem_read_byte(struct gb_s *gb, uint16_t off);
uint16_t mem_read_word(struct gb_s *gb, uint16_t off);

void mem_write_byte(struct gb_s *gb, uint16_t off, uint8_t val);
void mem_write_word(struct gb_s *gb, uint16_t off, uint16_t val);

#endif /* !BOI_MEM_H */
