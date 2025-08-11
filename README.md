# OS Development Learning Project (32-bit)

This repository contains my journey through learning operating system development for 32-bit architecture. Each directory represents a different stage of the learning process, progressively building up from bare metal to more complex OS features.

## Project Structure

1. `1_bare_metal/` - Basic bootloader and kernel setup
2. `2_VGA/` - VGA text mode implementation
3. `3_GDT/` - Global Descriptor Table implementation
4. `4_TSS/` - Task State Segment setup
5. `5_IDT/` - Interrupt Descriptor Table implementation
6. `6_PIT/` - Programmable Interval Timer
7. `7_PS2/` - PS/2 Keyboard driver
8. `8_MB_MEM_MAPS/` - Multiboot memory maps
9. `9_PAGING_HIGHER_HALF/` - Higher half kernel and paging setup
10. `10_MEM_MAN_PAGING/` - Memory management with paging
11. `11_KMALLOC/` - Kernel memory allocator implementation

## Features

- Bare metal x86 (32-bit) development
- Custom bootloader using GRUB
- Memory management (paging, higher half kernel)
- Hardware interaction (VGA, keyboard)
- Interrupt handling
- Memory allocation

## Building and Running

Each directory contains its own `Makefile` for building the specific stage. To build any stage:

```bash
cd <stage_directory>
make
```

This will create an ISO file in the `iso/` directory that can be run in QEMU or other virtual machines.

## Requirements

- GNU Make
- NASM assembler
- GCC cross-compiler for i686-elf
- GRUB bootloader tools
- QEMU for testing (recommended)

* I followed the Cross-Compiler instructions for i386 OS development from the OS Dev Wiki in the 'Cross Compiler' section.
* You can use either NASM (Intel) Assembly or GCC Assembly (AT&T) Assembly for the standalone assembly files.
* I used both NASM and GAS (GCC Assembly) for my bootloaders, starting from Intel Assembly (using NASM) to GAS Assembly (using GCC cross-compiler).

## Learning Resources

This project follows various OS development tutorials and resources, including:
- OSDev Wiki (https://wiki.osdev.org)
- Writing a Simple Operating System from Scratch
- OPerating Systems Development by 'Oliver Stream' YouTube Channel.

## Folder Structure

Each stage follows a similar directory structure:

```
stage_directory/
├── Makefile                # Build configuration
├── build/                  # Compiled object files
│   ├── boot.o
│   ├── kernel.o
│   └── other_modules.o
├── iso/                    # Output directory for bootable ISO
│   └── myos.iso
├── kernel/                 # Kernel source code
│   ├── includes/          # Header files
│   │   ├── gdt/
│   │   ├── idt/
│   │   ├── keyboard/
│   │   └── memory/
│   └── src/              # Implementation files
└── MyOS/                  # Boot directory
    └── boot/             # Bootloader files
```

## Note

This is a learning project focused on understanding OS internals and low-level programming concepts. Each stage builds upon the previous one, demonstrating progressive implementation of OS features.

**Note:** The ISO file (`myos.iso`) inside the `iso` directory can be run on real hardware. 