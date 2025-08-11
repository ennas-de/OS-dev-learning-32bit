#include "utils/util.h"

void memset(void* dest, char val, uint32_t count) {
    char* temp = (char *)dest;
    
    for (; count != 0; count--) {       
        *temp++ = val;
    }
}

void outPortB(uint16_t Port, uint8_t Value) {
    asm volatile("outb %1, %0" :: "dN"(Port), "a"(Value));
}

// uint8_t inPortB(uint16_t Port) {
//     uint8_t ret;
//     asm volatile("inb %1, %0" : "=a"(ret) : "dN"(Port));
//     return ret;
// }