#ifndef TIMER_H
#define TIMER_H

#include "nostdlib/stdint.h"
#include "utils/util.h"

void timer_init(void);
void set_timer_frequency(uint32_t frequency);
void timer_handler(void);
void timer_sleep(uint32_t milliseconds);
void on_irq_0(struct InterruptRegisters *regs);

#endif
