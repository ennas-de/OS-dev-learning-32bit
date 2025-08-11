// #include "vga/vga.h"
// #include "stdlib/stdint.h"
// #include "stdlib/stddef.h"

// uint16_t            screen_buffer[VGA_HEIGHT * 2 * VGA_WIDTH];  // Buffer twice the screen size
// uint16_t*           vga_buffer      = VGA_MEMORY;
// uint16_t            column          = 0;
// uint16_t            line            = 0;
// uint16_t            buffer_start    = 0;            // First visible line in buffer
// const uint16_t      default_color   = (LIGHT_GREY << 8) | (BLACK << 12);
// uint16_t            current_color   = default_color;

// const uint16_t      make_vga_entry (char c, uint16_t color) {
//     return (uint16_t)c | ((uint16_t)color << 8);
// }

// void set_text_color (enum vga_colors fg, enum vga_colors bg) {
//     current_color = fg | (bg << 4);
// }

// void reset() {
//     column          = 0;
//     line            = 0;
//     buffer_start    = 0;

//     // Clear entire buffer
//     for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
//         for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//             screen_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ', default_color);
//         }
//     }

//     // Clear screen
//     for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
//         for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//             vga_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ', default_color);
//         }
//     }
// }

// void clear_screen() {
//     column          = 0;
//     line            = 0;

//     for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
//         for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//             vga_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ', current_color);
//         }
//     }
// }

// void update_screen() {
//     // Copy visible portion from screen buffer to VGA memory
//     for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
//         for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//             vga_buffer[y * VGA_WIDTH + x] = screen_buffer[(buffer_start + y) * VGA_WIDTH + x];
//         }
//     }
// }

// void scroll_up() {
//     // If we're at the end of our buffer
//     if (line >= (VGA_HEIGHT * 2) - 1) {
//         // Move everything up by half the screen
//         for (uint16_t y = VGA_HEIGHT; y < VGA_HEIGHT * 2; y++) {
//             for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//                 screen_buffer[(y - VGA_HEIGHT) * VGA_WIDTH + x] = screen_buffer[y * VGA_WIDTH + x];
//             }
//         }
//         // Adjust line and buffer_start
//         line -= VGA_HEIGHT;
//         buffer_start -= VGA_HEIGHT;
//         if (buffer_start < 0) buffer_start = 0;
//     }
    
//     // Clear the next line
//     for (uint16_t x = 0; x < VGA_WIDTH; x++) {
//         screen_buffer[(line + 1) * VGA_WIDTH + x] = make_vga_entry(' ', current_color);
//     }

//     // If we're past the visible area, scroll the view
//     if (line >= buffer_start + VGA_HEIGHT - 1) {
//         buffer_start = line - VGA_HEIGHT + 1;
//     }

//     update_screen();
// }

// void scroll_page_up() {
//     if (buffer_start > 0) {
//         buffer_start -= VGA_HEIGHT;
//         if (buffer_start < 0) buffer_start = 0;
//         update_screen();
//     }
// }

// void scroll_page_down() {
//     uint16_t max_start = (line > VGA_HEIGHT - 1) ? line - VGA_HEIGHT + 1 : 0;
//     if (buffer_start < max_start) {
//         buffer_start += VGA_HEIGHT;
//         if (buffer_start > max_start) buffer_start = max_start;
//         update_screen();
//     }
// }

// void new_line() {
//     column = 0;
//     line++;
    
//     // If we've moved past the visible area
//     if (line >= buffer_start + VGA_HEIGHT) {
//         scroll_up();
//     }
// }

// void print_char (char c) {
//     switch (c) {
//         case '\n':
//             new_line();
//             break;
//         case '\t':
//             if (column == VGA_WIDTH) {
//                 new_line();
//             }

//             uint16_t tab_len = 4 - (column % 4);

//             while (tab_len != 0) {
//                 screen_buffer[line * VGA_WIDTH + column] = make_vga_entry(' ', current_color);
//                 vga_buffer[(line - buffer_start) * VGA_WIDTH + column] = make_vga_entry(' ', current_color);
//                 column++;
//                 tab_len--;
//             }
//             break;
//         case '\r':
//             column = 0;
//             break;
//         default:
//             if (column == VGA_WIDTH) new_line();

//             screen_buffer[line * VGA_WIDTH + column] = make_vga_entry(c, current_color);
//             if (line >= buffer_start && line < buffer_start + VGA_HEIGHT) {
//                 vga_buffer[(line - buffer_start) * VGA_WIDTH + column] = make_vga_entry(c, current_color);
//             }
//             column++;
//     };

// }

// void print_str(const char* str) {
//     for (size_t i = 0; str[i] != '\0'; i++) {
//         print_char(str[i]);
//     }
// }

// void vga_init() {
//     reset();
// }