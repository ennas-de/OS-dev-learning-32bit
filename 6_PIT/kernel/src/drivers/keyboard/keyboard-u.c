// #include "keyboard/keyboard.h"
// #include "vga/vga.h"
// #include "utils/util.h"

// #define KEYBOARD_DATA_PORT 0x60
// #define PAGE_UP   0x49
// #define PAGE_DOWN 0x51

// void keyboard_handler(struct InterruptRegisters *regs) {
//     uint8_t scancode = inPortB(KEYBOARD_DATA_PORT);
    
//     switch(scancode) {
//         case PAGE_UP:
//             scroll_page_up();
//             break;
//         case PAGE_DOWN:
//             scroll_page_down();
//             break;
//         default:
//             break;
//     }
// }

// void keyboard_init() {
//     // Install keyboard handler for IRQ1
//     irq_install_handler(1, keyboard_handler);
// }
