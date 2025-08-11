BITS            32

section         .text
                align   4
                dd      0x1BADB002
                dd      0x00000003
                dd      -(0x01BADB002 + 0x00000003)

global          start
extern          kernel_main

start:
                cli
                mov esp, stack_top
                call kernel_main
                halt

halt:
                cli
                hlt
                jmp halt

section         .bss
stack_bottom:
RESB            8192
stack_top:
