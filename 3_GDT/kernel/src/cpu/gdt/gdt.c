#include "vga/vga.h"

/** GDT entry structure */
struct gdt_entry_struct {
    uint16_t limit_low;         // Bits 0-15 of segment limit
    uint16_t base_low;          // Bits 0-15 of segment base
    uint8_t base_middle;        // Bits 16-23 of segment base
    uint8_t access;             // Access Flags
    uint8_t flags;              // Granularity + bits 16-19 of segment limit
    uint8_t base_high;          // Bits 24-31 of segment base
}__attribute__((packed));

/** GDT pointer (used by lgdt) */
struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

extern void gdt_load(uint32_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;                      // descriptor

/** Set GDT entry */
void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[index].base_low     = (base & 0xFFFF);  
    gdt_entries[index].base_middle  = (base >> 16) & 0xFF;
    gdt_entries[index].base_high    = (base >> 24) & 0xFF;
    
    gdt_entries[index].limit_low    = (limit & 0xFFFF);
    gdt_entries[index].flags        = (limit >> 16) & 0xFF;
    gdt_entries[index].flags        |= (gran & 0xFF);

    gdt_entries[index].access       = access;
} 

void gdt_init() {
    gdt_ptr.limit   = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base    = (uint32_t) &gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0);                   // NULL segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);    // Kernel code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);    // Kernel data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);    // User code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);    // Kernel data segment

    gdt_load((uint32_t)&gdt_ptr);
}



