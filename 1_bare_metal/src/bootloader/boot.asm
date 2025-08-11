BITS 32

section .text
    align   4
    dd      0x1BADB002                  ; MAGIC
    dd      0x00000003                  ; FLAGS: ALIGN | MEMINFO
    dd      -(0x1BADB002 + 0x00000003)  ; CHECKSUM

global      start 
extern      kernel_main 

start:
    CLI 
    MOV     esp, stack_top
    CALL    kernel_main
    HLT 

Halt:
    CLI 
    HLT
    JMP Halt

section     .bss 
stack_bottm:
RESB        8192
stack_top: