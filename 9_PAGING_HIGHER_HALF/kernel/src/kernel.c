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
    // memory_init(boot_info);

    print_str("Hello!\n");
    print_str("VGA Initialized.\n");
    print_str("GDT Initialized (with TSS).\n");
    print_str("IDT Initialized.\n");
    print_str("PIT Timer Initialized.\n");
    print_str("PS2 - Keyboard Initialized.\n");
    // print_str("Multiboot Memory Maps Initialized.\n");
    print_str("Paging & Higher Half Initialized.\n");
}