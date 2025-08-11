#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "utils/util.h"

void keyboard_init();
void keyboard_handler(struct InterruptRegisters *regs);

#endif
