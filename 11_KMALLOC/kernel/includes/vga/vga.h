#ifndef VGA_H
#define VGA_H

#include "nostdlib/stdint.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  (uint16_t *)0xB8000

enum vga_colors {
    BLACK           = 0,
    BLUE            = 1,
    GREEN           = 2,
    CYAN            = 3,
    RED             = 4,
    MAGENTA         = 5,
    BROWN           = 6,
    LIGHT_GREY      = 7,
    DARK_GREY       = 8,
    LIGHT_BLUE      = 9,
    LIGHT_GREEN     = 10,
    LIGHT_CYAN      = 11,
    LIGHT_RED       = 12,
    LIGHT_MAGENTA   = 13,
    LIGHT_BROWN     = 14,
    WHITE           = 15
};

void vga_init();
void reset();
void clear_screen();
void print_char(char c);
void print_str(const char* str);
void scroll_up();
void new_line();
void set_text_color(enum vga_colors fg, enum vga_colors bg);

#endif