# Tooling
CC 		= gcc
ASM		= nasm
LD		= ld

# Compiler flags
CFLAGS	= -fno-stack-protector -fno-builtin -nostdlib -Ikernel/include

# Folder Structure
SRC 	= kernel/src
INCLUDE	= kernel/include
BUILD	= build
ISO		= iso
MYOS	= MyOS
BOOT	= $(MYOS)/boot
#
DRIVERS	= $(SRC)/drivers

# Instructions
all: clean run

clean:
	rm -rf $(BUILD)/*.o
	rm -rf $(ISO)/myos.iso
	rm -rf $(BOOT)/kernel

boot: $(SRC)/bootloader/boot.s
	$(ASM) -f elf32 $(SRC)/bootloader/boot.s -o $(BUILD)/boot.o
	$(ASM) -f elf32 $(SRC)/cpu/gdt/gdt_load.s -o $(BUILD)/gdt_load.o

kernel: $(SRC)/kernel.c
	# 	$(CC) -g -m32 $(CFLAGS) -c $(DRIVERS)/vga/vga.c -o $(BUILD)/vga.o 		# This is used for debuging with GDT
	$(CC) -m32 $(CFLAGS) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o
	$(CC) -m32 $(CFLAGS) -c $(SRC)/cpu/gdt/gdt.c -o $(BUILD)/gdt.o
	$(CC) -m32 $(CFLAGS) -c $(DRIVERS)/vga/vga.c -o $(BUILD)/vga.o

image: boot kernel
	$(LD) -m elf_i386 -T $(SRC)/linker.ld -o $(BOOT)/kernel $(BUILD)/*.o
	grub-mkrescue -o $(ISO)/myos.iso $(MYOS)/

run: image
# 	qemu-system-i386 -s -S $(ISO)/myos.iso # Flags for debugging
	qemu-system-i386 $(ISO)/myos.iso