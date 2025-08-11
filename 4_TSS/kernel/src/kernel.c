#include "vga/vga.h"
#include "gdt/gdt.h"

void kernel_main(void) {
    vga_init();
    set_text_color(WHITE, BLACK);

    gdt_init();

    print_str("Hello!\n");
    print_str("VGA Initialized.\n");
    print_str("GDT Initialized (with TSS).\n");
}