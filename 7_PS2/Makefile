# Tooling
CC		= /usr/opt/cross/bin/i686-elf-gcc
ASM		= /usr/opt/cross/bin/i686-elf-as
LD		= /usr/opt/cross/bin/i686-elf-ld

# Compiler flags
CFLAGS	= -O2 -g -ffreestanding -Wall -Wextra -Ikernel/includes

# Folder structure
SRC		= kernel/src
INCLUDE	= kernel/includes
BUILD	= build
ISO		= iso
MYOS	= MyOS
BOOT	= $(MYOS)/boot
#
DRIVERS = $(SRC)/drivers
CPU 	= $(SRC)/cpu

# Instructions
all: clean run

clean:
		rm -rf $(BUILD)/*.o
		rm -rf $(ISO)/myos.iso
		rm -rf $(BOOT)/kernel

boot: $(SRC)/bootloader/boot.s
	$(ASM) $(SRC)/bootloader/boot.s -o $(BUILD)/boot.o
	$(ASM) $(SRC)/cpu/gdt/gdt.s -o $(BUILD)/gdts.o
	$(ASM) $(SRC)/cpu/idt/idt.s -o $(BUILD)/idts.o

kernel: $(SRC)/kernel.c
	$(CC) $(CFLAGS) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o
	$(CC) $(CFLAGS) -c $(DRIVERS)/vga/vga.c -o $(BUILD)/vga.o
	$(CC) $(CFLAGS) -c $(SRC)/utils/util.c -o $(BUILD)/util.o
	$(CC) $(CFLAGS) -c $(CPU)/gdt/gdt.c -o $(BUILD)/gdt.o
	$(CC) $(CFLAGS) -c $(CPU)/idt/idt.c -o $(BUILD)/idt.o
	$(CC) $(CFLAGS) -c $(CPU)/timer/timer.c -o $(BUILD)/timer.o
	$(CC) $(CFLAGS) -c $(SRC)/stdlib/stdio/stdio.c -o $(BUILD)/stdio.o
	$(CC) $(CFLAGS) -c $(DRIVERS)/keyboard/keyboard.c -o $(BUILD)/keyboard.o

image: boot kernel
	$(LD) -m elf_i386 -T $(SRC)/linker.ld -o $(BOOT)/kernel $(BUILD)/*.o
	grub-mkrescue -o $(ISO)/myos.iso $(MYOS)/

run: image
	qemu-system-i386 $(ISO)/myos.iso