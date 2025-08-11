; GDT Loader
section .text
global  gdt_flush
global tss_flush

gdt_flush:
    mov eax, [esp + 4]            ; Load the pointer argument
    lgdt [eax]                  ; Load the GDT

    ; Reload segmen registers
    mov ax, 0x10               ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Far jump to reload CS
    jmp 0x08:.flush            ; 0x08 is code segment selector

.flush:                         ; Now we're in the new code segment
    ret
tss_flush:
    mov ax, 0x2B
    ltr ax
    ret
