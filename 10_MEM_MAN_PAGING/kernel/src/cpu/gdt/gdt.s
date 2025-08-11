// GDT Loader
.section .text
.global gdt_flush
.global tss_flush

gdt_flush:
    movl 4(%esp), %eax         // Load the pointer argument
    lgdt (%eax)                // Load the GDT

    // Reload segment registers
    movw $0x10, %ax           // Data segment selector
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    // Far jump to reload CS
    ljmp $0x08, $flush        // 0x08 is code segment selector

flush:                        // Now we're in the new code segment
    ret

tss_flush:
    movw $0x2B, %ax
    ltr %ax
    ret
