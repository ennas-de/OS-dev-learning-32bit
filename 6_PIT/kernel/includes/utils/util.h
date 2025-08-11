#ifndef UTIL_H
#define UTIL_H

#include "nostdlib/stdint.h"

void memset(void *dest, char val, uint32_t count);
void outPortB(uint16_t Port, uint8_t Value);
uint8_t inPortB(uint16_t Port);

struct InterruptRegisters {
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

#endif