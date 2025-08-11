# compler and tools
CC		= gcc
ASM		= nasm
LD      = ld

# # folder structure
# SRC     = src
# BUILD   = build
# BOOT    = boot
# ISO     = iso

# # files 
# KERNEL_SRC	= $(SRC)/kernel.c
# BOOT_SRC	= $(SRC)/bootloader/boot.s
# LINKER		= $(SRC)/linker.ld

# KERNEL_OBJ	= $(BUILD)/kernel.o
# BOOT_OBJ	= $(BUILD)/boot.o
# KERNEL_BIN	= $(BOOT)/kernel
# ISO_IMG		= $(ISO)/kernel.iso

.PHONY: all clean kernel boot image run 

all: clean boot kernel image run 

clean:
	rm -rf build/*.o
	rm -rf MyOS/boot/kernel
	rm -rf iso/kernel.iso

kernel: 
	$(CC) -m32 -fno-stack-protector -fno-builtin -nostdlib -c src/kernel.c -o build/kernel.o

boot: 
	$(ASM) -f elf32 src/bootloader/boot.asm -o build/boot.o

image: 
	$(LD) -m elf_i386 -T src/linker.ld -o MyOS/boot/kernel build/boot.o build/kernel.o
	grub-mkrescue -o iso/kernel.iso MyOS/

run: 
	qemu-system-i386 -cdrom iso/kernel.iso