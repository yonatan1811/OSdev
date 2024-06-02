#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../CPU/idt.h"
void keyboard_handler(struct regs *r);
void kb_install();
#endif