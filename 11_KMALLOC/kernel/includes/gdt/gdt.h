#ifndef GDT_H
#define GDT_H

#include "nostdlib/stdint.h"

void gdt_init();
void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0);

#endif