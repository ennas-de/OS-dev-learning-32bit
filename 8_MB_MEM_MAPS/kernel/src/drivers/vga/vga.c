#include "vga/vga.h"
#include "nostdlib/stdint.h"
#include "nostdlib/stddef.h"

uint16_t*       vga_buffer      = VGA_MEMORY;
uint16_t        column          = 0;
uint16_t        line            = 0;
const uint16_t  default_color   = (LIGHT_GREY << 8) | (BLACK << 12);
uint16_t        current_color   = default_color;

uint16_t make_vga_entry(char c, uint16_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void set_text_color(enum vga_colors fg, enum vga_colors bg) {
    current_color = fg | (bg << 4);
}

void reset (){
    column  = 0;
    line    = 0;

    for (uint16_t y= 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ', default_color);
        }
    }
}

void clear_screen() {
    column  = 0;
    line    = 0;

    for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = make_vga_entry(' ', current_color);
        }
    }
}

void scroll_up() {
    for (uint16_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y-1) * VGA_WIDTH + x] = vga_buffer[y * VGA_WIDTH + x];
        }
    }
}

void new_line() {
    if (line < VGA_HEIGHT - 1) {
        line++;
        column = 0;
    } else {
        scroll_up();
        column = 0;
    }
}

void print_char(char c) {
    switch (c) {
        case '\n':
            new_line();
            break;
        case '\t':
            if (column == VGA_WIDTH) new_line();

            uint16_t tab_len = 4 - (column % 4);

            while (tab_len != 0) {
                vga_buffer[line * VGA_WIDTH + column++] = make_vga_entry(' ', current_color);
                tab_len--;
            }
            break;
        case '\r':
            column = 0;
            break;
        default:
            if (column == VGA_WIDTH) new_line();

            vga_buffer[line * VGA_WIDTH + column++] = make_vga_entry(c, current_color);
    };
}

void print_str(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++){
        print_char(str[i]);
    }
}

void vga_init() {
    reset();
}