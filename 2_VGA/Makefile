# Tooling
CC 			= gcc
ASM			= nasm
LD			= ld

# Compiler Default
# CFLAGS? = # -O2 -g

# Compiler Flags
CFLAGS = -fno-stack-protector -fno-builtin -nostdlib -I./kernel/include
# CFLAGS = $(CFLAGS) -fno-stack-protector -fno-builtin -nostdlib -I./kernel/include

# folders
BUILD		= build
INCLUDE		= kernel/include
ISO			= iso
SRC			= kernel/src
MYOS		= MyOS
BOOT		= $(MYOS)/boot

all: clean boot kernel image run

clean:
	rm -rf $(BUILD)/*.o
	rm -rf $(ISO)/kernel.iso
	rm -rf $(BOOT)/kernel

boot: $(SRC)/bootloader/boot.asm
	$(ASM) -f elf32 $(SRC)/bootloader/boot.asm -o $(BUILD)/boot.o

kernel: $(SRC)/kernel.c
	$(CC) -m32 $(CFLAGS) -c $(SRC)/kernel.c -o $(BUILD)/kernel.o
	$(CC) -m32 $(CFLAGS) -c $(SRC)/vga/vga.c -o $(BUILD)/vga.o

image: boot kernel
	$(LD) -m elf_i386 -T $(SRC)/linker.ld -o $(BOOT)/kernel $(BUILD)/*.o
	grub-mkrescue -o $(ISO)/myos.iso $(MYOS)/

run: image
	qemu-system-i386 $(ISO)/myos.iso
