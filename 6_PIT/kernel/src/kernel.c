#include "vga/vga.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "timer/timer.h"

void kernel_main(void) {
    vga_init();
    set_text_color(WHITE, BLACK);

    gdt_init();
    idt_init();
    timer_init();
    // keyboard_init();

    print_str("Hello!\n");
    print_str("VGA Initialized.\n");
    print_str("GDT Initialized (with TSS).\n");
    print_str("IDT Initialized.\n");
    print_str("PIT Timer Initialized.\n");
    // print_str("Keyboard Initialized.\n");
}