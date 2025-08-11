// #include "nostdlib/stdint.h"
#include "stdlib/stdio.h"
#include "memory/memory.h"

void memory_init(struct multiboot_info* boot_info) {
    for (int i = 0; i < boot_info->mmap_length; i += sizeof(struct multiboot_mmap_entry)) {
        struct multiboot_mmap_entry *mmmt = (struct multiboot_mmap_entry*)(boot_info->mmap_addr + i);

        printf(
            "Low Add: %x | Higher Addr: %x | Low Length: %x | High Length: %x | Size: %x | Type: %d\n", 
            mmmt->addr_low, mmmt->addr_high, mmmt->len_low, mmmt->len_high, mmmt->size, mmmt->type
        );
    }
}