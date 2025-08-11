#include "gdt/gdt.h"
#include "utils/util.h"

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

struct tss_entry_struct {
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint32_t trap;
    uint32_t iomap_base
}__attribute__((packed));

extern void gdt_flush(uint32_t);
extern void tss_flush();

struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;      // descriptor
struct tss_entry_struct tss_entry;

/** Set GDT Entry */
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
    gdt_ptr.limit   = (sizeof(struct gdt_entry_struct) * 6) - 1;
    gdt_ptr.base    = (uint32_t) &gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0);                   // NULL segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);    // Kernel code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);    // Kernel data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);    // User code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);    // Kernel data segment

    writeTSS(5, 0x10, 0x0);
    gdt_flush((uint32_t)&gdt_ptr);
    tss_flush();
}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0) {
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);

    set_gdt_entry(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0   = ss0;
    tss_entry.esp0  = esp0;

    tss_entry.cs    = 0x08 | 0x3;
    tss_entry.ss    = tss_entry.ds  = tss_entry.es  = tss_entry.fs  = tss_entry.gs  = 0x10 | 0x3;
}



