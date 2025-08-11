#include "utils/util.h"
#include "memory/memory.h"
#include "nostdlib/stdbool.h"
#include "kmalloc/kmalloc.h"
#include "vga/vga.h"

static uint32_t heap_start;
static uint32_t heap_size;
static uint32_t threshold;
static bool kmalloc_initialized = false;

void kmalloc_init(uint32_t initial_heap_size) {
    if (kmalloc_initialized) {
        // print_str("kmalloc already initialized\n");
        return;
    }
    
    heap_start = KERNEL_MALLOC;
    heap_size = 0;
    threshold = 0;
    
    // Ensure initial heap size is page-aligned
    initial_heap_size = CEIL_DIV(initial_heap_size, 0x1000) * 0x1000;
    
    // Try to change heap size before marking as initialized
    change_heap_size(initial_heap_size);
    
    // Only mark as initialized if we successfully allocated the initial pages
    if (heap_size >= initial_heap_size) {
        kmalloc_initialized = true;
        // print_str("kmalloc initialized successfully at 0x");
        // print_str("\n");
    } else {
        print_str("Failed to initialize kmalloc. Heap size: ");
        // print_hex(heap_size);
        print_str("\n");
    }
}

void change_heap_size(int new_size) {
    print_str("Changing heap size...\n");
    
    if (new_size < 0) {
        print_str("Invalid heap size requested\n");
        return;
    }

    int old_page_count = heap_size / 0x1000;
    int new_page_count = CEIL_DIV(new_size, 0x1000);

    if (new_page_count > old_page_count) {
        int pages_to_add = new_page_count - old_page_count;
        // print_str("Adding pages: ");
        // // print_hex(pages_to_add);
        // print_str("\n");
        
        for (int i = 0; i < pages_to_add; i++) {
            uint32_t phys = pmm_alloc_page_frame();
            if (!phys) {
                print_str("Failed to allocate physical page\n");
                return;
            }
            
            uint32_t virt = KERNEL_MALLOC + (old_page_count + i) * 0x1000;
            
            mem_map_page(virt, phys, PAGE_FLAG_WRITE | PAGE_FLAG_PRESENT);
            
            // Zero out the new page
            memset((void*)virt, 0, 0x1000);
        }
        
        heap_size = new_page_count * 0x1000;  // Update size only after successful allocation
        // print_str("Heap size changed successfully\n");
    } else {
        heap_size = new_page_count * 0x1000;
        // print_str("Heap size reduced\n");
    }
}

void* kmalloc(uint32_t size) {
    if (!kmalloc_initialized || size == 0) return 0;

    // Align size to 4-byte boundary
    size = (size + 3) & ~3;

    // Check if we need more space
    if (threshold + size > heap_size) {
        // Calculate needed pages (round up to nearest page)
        uint32_t pages_needed = CEIL_DIV(size, 0x1000);
        uint32_t new_size = heap_size + (pages_needed * 0x1000);
        
        // Try to grow the heap
        change_heap_size(new_size);
        
        // Verify we have enough space after growing
        if (threshold + size > heap_size) {
            return 0;  // Failed to allocate enough space
        }
    }

    void* ptr = (void*)(heap_start + threshold);
    threshold += size;
    return ptr;
}