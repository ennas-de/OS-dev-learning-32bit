#include "vga/vga.h"

void kernel_main(void);

void kernel_main(void){
    vga_init();
    set_text_color(WHITE, BLACK);

    print_str("Welcome to MyOS!\n");
    print_str("VGA Initialized.\n");
}