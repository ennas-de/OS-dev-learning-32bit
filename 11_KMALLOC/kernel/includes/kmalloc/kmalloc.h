#ifndef KMALLOC_H
#define KMALLOC_H

#include "nostdlib/stdint.h"

void kmalloc_init(uint32_t heap_size);
void change_heap_size(int new_size);
void* kmalloc(uint32_t size);

#endif