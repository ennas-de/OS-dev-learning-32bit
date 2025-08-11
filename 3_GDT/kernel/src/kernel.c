#include "vga/vga.h"
#include "gdt/gdt.h"

void kernel_main(void) {
    vga_init();
    set_text_color(WHITE, BLACK);

    gdt_init();

    print_str("\tHELLO!\n");
    print_str("Welcome to 'myos' operating system.\n");

    print_str("VGA Initialized!\n");
    print_str("GDT Initialized!");

    // for (uint8_t i = 0; i < 100000; i++) {
    //     print_str("\nThis is line ");
    //     print_str((const char[]){'0' + i, '\0'});  // Convert number to string
    // }
}