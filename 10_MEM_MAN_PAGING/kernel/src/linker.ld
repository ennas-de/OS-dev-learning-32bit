ENTRY(_start)
SECTIONS {
    . = 0x00100000;  /* Start at 1MB physical */

    /* Critical: Place .boot FIRST with minimal padding */
    .boot : {
        *(.boot)
    }

    .note.gnu.build-id ALIGN(4K): {
        *(.note.gnu.built-id)
    }

    /* Higher half kernel from 0xC0000000 */
    . += 0xC0000000;

    /* Page-align sections after .boot */
    .text ALIGN(4K) : AT(ADDR(.text) - 0xC0000000) {
        *(.text)
    }
    .data ALIGN(4K) : AT(ADDR(.data) - 0xC0000000) {
        *(.data)
    }
    .bss ALIGN(4K) : AT(ADDR(.bss) - 0xC0000000) {
        *(.bss)
        *(COMMON)
    }
    _kernel_end = .;
}