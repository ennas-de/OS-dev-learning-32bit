#include "nostdlib/stdint.h"
#include "utils/util.h"
#include "idt/idt.h"
#include "vga/vga.h"
#include "timer/timer.h"

uint64_t ticks;
const uint32_t frequency = 100; // 100 Hz

void on_irq_0(struct InterruptRegisters *regs) {
    ticks++;

    // print_str("Tick: ");
    // print_str(ticks);
    // print_str("\n");
}

void timer_init(void) {
    ticks = 0;
    irq_install_handler(0, &on_irq_0);

    // 11931.81666666 / 100 Hz = 11931.81666666 = 1.1931816666 MHz      ??
    uint32_t divisor = 1193180 / frequency;

    // 0011 0110
    outPortB(0x43, 0x36); // Command byte: 00110110
    outPortB(0x40, (uint8_t)(divisor & 0xFF)); // Low byte
    outPortB(0x40, (uint8_t)((divisor >> 8) & 0xFF)); // High byte
}

void set_timer_frequency(uint32_t new_frequency) {
    if (new_frequency == 0) {
        return; // Avoid division by zero
    }
    
    uint32_t divisor = 1193180 / new_frequency;
    outPortB(0x43, 0x36); // Command byte: 00110110
    outPortB(0x40, (uint8_t)(divisor & 0xFF)); // Low byte
    outPortB(0x40, (uint8_t)((divisor >> 8) & 0xFF)); // High byte
}

void timer_handler(void) {
    // This function can be used to handle timer-specific tasks
    // For now, it does nothing as the IRQ handler is sufficient
}

void timer_sleep(uint32_t milliseconds) {
    uint64_t end_ticks = ticks + (milliseconds * frequency) / 1000;
    while (ticks < end_ticks) {
        // Busy wait until the specified time has passed
        // This is a simple implementation; consider using a more efficient sleep mechanism
        __asm__ volatile ("hlt"); // Halt the CPU to save power while waiting
        // This will also allow other interrupts to be processed
        // If you want to allow other tasks to run, you might want to yield the CPU here
        // For example, you could call a scheduler or a context switch function
        // scheduler_yield(); // Uncomment if you have a scheduler implemented
        // Note: Make sure that the scheduler or context switch function does not block
        // and allows the timer interrupt to be processed.
        // This is important to ensure that the ticks variable is updated correctly.
        // If you don't have a scheduler, the above hlt instruction will suffice.
        // It will halt the CPU until an interrupt occurs, allowing the timer interrupt to increment ticks.
        // This is a simple way to implement a sleep function in a bare-metal environment.
        // However, be cautious with busy waiting as it can lead to high CPU usage.
        // In a more advanced system, you would want to use a more efficient sleep mechanism.
        // For example, you could use a sleep queue or a task scheduler that allows other tasks to run
        // while waiting for the timer interrupt to wake up the sleeping task.
        // This would be more efficient and would not waste CPU cycles.
        // In summary, this simple implementation uses busy waiting and halts the CPU
        // until the specified time has passed, allowing the timer interrupt to update ticks.
        // This is sufficient for a basic timer sleep function in a bare-metal environment.
        // If you have a more complex system with a scheduler, consider using that instead.
        // This will allow other tasks to run and will not block the CPU.
        // If you don't have a scheduler, the above hlt instruction will suffice.
        // It will halt the CPU until an interrupt occurs, allowing the timer interrupt to increment ticks.
        // This is a simple way to implement a sleep function in a bare-metal environment.
        // However, be cautious with busy waiting as it can lead to high CPU usage.
        // In a more advanced system, you would want to use a more efficient sleep mechanism.
        // For example, you could use a sleep queue or a task scheduler that allows other tasks to run
        // while waiting for the timer interrupt to wake up the sleeping task.
        // This would be more efficient and would not waste CPU cycles.
        // In summary, this simple implementation uses busy waiting and halts the CPU
        // until the specified time has passed, allowing the timer interrupt to update ticks.
        // This is sufficient for a basic timer sleep function in a bare-metal environment.
        // If you have a more complex system with a scheduler, consider using that instead.
        // This will allow other tasks to run and will not block the CPU.
        // If you don't have a scheduler, the above hlt instruction will suffice.
        // It will halt the CPU until an interrupt occurs, allowing the timer interrupt to increment ticks.
        // This is a simple way to implement a sleep function in a bare-metal environment.
        // However, be cautious with busy waiting as it can lead to high CPU usage.
        // In a more advanced system, you would want to use a more efficient sleep mechanism.
        // For example, you could use a sleep queue or a task scheduler that allows other tasks to run
        // while waiting for the timer interrupt to wake up the sleeping task.
        // This would be more efficient and would not waste CPU cycles.
        // In summary, this simple implementation uses busy waiting and halts the CPU
        // until the specified time has passed, allowing the timer interrupt to update ticks.
    }
}