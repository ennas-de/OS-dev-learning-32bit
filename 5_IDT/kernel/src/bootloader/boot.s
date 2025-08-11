BITS            32

section         .text
                ; multiboot header (must be within 8KiB of the boot sector)
                align       4
                dd          0x1BADB002      ; MAGIC
                dd          0x00000003      ; FLAGS (ALIGN | MEMINFO)
                dd          -(0x1BADB002 + 0x00000003)  ; CHECKSUM: Inverse (MAGIC + FLAGS)

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