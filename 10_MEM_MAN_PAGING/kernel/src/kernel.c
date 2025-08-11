#include "vga/vga.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "timer/timer.h"
#include "keyboard/keyboard.h"
#include "multiboot/multiboot.h"
#include "memory/memory.h"

void kernel_main(uint32_t magic, struct multiboot_info* boot_info) {
    vga_init();
    set_text_color(WHITE, BLACK);

    gdt_init();
    idt_init();
    timer_init();
    keyboard_init();

    // Default physical allocation start if no modules
    uint32_t physical_alloc_start = 0x100000;  // Start at 1MB by default

    // Check if we have modules and update physical_alloc_start if we do
    if (boot_info->flags & (1 << 3) && boot_info->mods_count > 0) {
        uint32_t mod1 = *(uint32_t*)(boot_info->mods_addr + 4);
        physical_alloc_start = (mod1 + 0xFFF) & ~0xFFF;
    }

    // memory_init(boot_info->mem_upper * 1024, "Memory Init");
    memory_init(boot_info->mem_upper * 1024, physical_alloc_start);
    
    print_str("Hello!\n");
    print_str("VGA Initialized.\n");
    print_str("GDT Initialized (with TSS).\n");
    print_str("IDT Initialized.\n");
    print_str("PIT Timer Initialized.\n");
    print_str("PS2 - Keyboard Initialized.\n");
    print_str("Multiboot Memory Maps Initialized.\n");
    print_str("Paging & Higher Half Initialized.\n");
    print_str("Memory Management and Paging implemented.\n");

    for(;;);
}