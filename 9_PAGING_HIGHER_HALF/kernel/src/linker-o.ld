ENTRY(_start)

SECTIONS
{
    /* Kernel starts at 1MB in memory */
    . = 1M;

    /* Place multiboot header first */
    .text BLOCK(4K) : ALIGN (4K)
    {
        *(.multiboot)
        *(.text*)
    }

    .rodata BLOCK(4K) : ALIGN (4K)
    {
        *(.rodata*)
    }

    .data BLOCK(4K) : ALIGN (4K)
    {
        *(.data*)
    }

    .bss BLOCK(4K) : ALIGN (4K)
    {
        *(COMMON)
        *(.bss*)
    }
}
