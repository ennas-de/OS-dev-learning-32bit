# Tooling
CC		= gcc
ASM		= nasm
LD		= ld

# Compiler flags
CFLAGS	= -fno-stack-protector -fno-builtin -nostdlib -Ikernel/include

# Folder structure
SRC		= kernel/src
INCLUDE	= kernel/include
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
	$(ASM) -f elf32 $(SRC)/bootloader/boot.s -o $(BUILD)/boot.o
	$(ASM) -f elf32 $(SRC)/cpu/gdt/gdt.s -o $(BUILD)/gdts.o
	$(ASM) -f elf32 $(SRC)/cpu/idt/idt.s -o $(BUILD)/idts.o

kernel: $(SRC)/kernel.c
	$(CC) -m32 $(CFLAGS) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o
	$(CC) -m32 $(CFLAGS) -c $(DRIVERS)/vga/vga.c -o $(BUILD)/vga.o
	$(CC) -m32 $(CFLAGS) -c $(SRC)/utils/util.c -o $(BUILD)/util.o
	$(CC) -m32 $(CFLAGS) -c $(CPU)/gdt/gdt.c -o $(BUILD)/gdt.o
	$(CC) -m32 $(CFLAGS) -c $(CPU)/idt/idt.c -o $(BUILD)/idt.o
# 	$(CC) -m32 $(CFLAGS) -c $(DRIVERS)/keyboard.c -o $(BUILD)/keyboard.o

image: boot kernel
	$(LD) -m elf_i386 -T $(SRC)/linker.ld -o $(BOOT)/kernel $(BUILD)/*.o
	grub-mkrescue -o $(ISO)/myos.iso $(MYOS)/

run: image
	qemu-system-i386 $(ISO)/myos.iso