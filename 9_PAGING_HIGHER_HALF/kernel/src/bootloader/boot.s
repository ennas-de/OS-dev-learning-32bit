
.section .boot, "ax"  # Allocatable+executable

# Multiboot Header
.align 4
.long 0x1BADB002       # MBOOT_MAGIC
.long 0x00000003       # Flags: PAGE_ALIGN | MEM_INFO
.long 0xE4524FFB       # Checksum: -(0x1BADB002 + 3)


.section .bss
.align 16
stack_bottom:
    .skip 16384 * 8
stack_top:

.section .boot

.global _start
_start:
    mov $(initial_page_dir - 0xC0000000), %ecx
    mov %ecx, %cr3

    mov %cr4, %ecx
    or $0x10, %ecx
    mov %ecx, %cr4

    mov %cr0, %ecx
    or $0x80000000, %ecx
    mov %ecx, %cr0

    jmp higher_half

.section .text
higher_half:
    mov $stack_top, %esp
    push %ebx
    push %eax
    xor %ebp, %ebp
    .extern kernel_main
    call kernel_main

halt:
    hlt
    jmp halt

.section .data
.align 4096
.global initial_page_dir
initial_page_dir:
    .long 0x83  // 10000011b
    .fill 767, 4, 0  // TIMES 768-1 DD 0

    .long ((0 << 22) | 0x83)  // 10000011b
    .long ((1 << 22) | 0x83)
    .long ((2 << 22) | 0x83)
    .long ((3 << 22) | 0x83)
    .fill 252, 4, 0  // TIMES 256-4 DD 0
