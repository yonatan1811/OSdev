#ifndef FS_H
#define FS_H
#include "./Typedefs.h"
//we will be using assmebly here again



/*
This family of functions is used to do low-level port input and
       output.  The out* functions do port output, the in* functions do
       port input; the b-suffix functions are byte-width
*/
//this function will receive 8 bits data from some port.
void outb(uint16_t port, uint8_t data);

void outl(uint16_t port, uint32_t value);

uint8_t inb(uint16_t port);


uint16_t inw(uint16_t port);


#endif