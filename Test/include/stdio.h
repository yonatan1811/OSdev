#ifndef _STDIO_H
#define _STDIO_H 1
 
#include "cdefs.h"
#include "terminal.h"
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif
 

int My_printf(const char* __restrict, ...);
int My_putchar(int int_char , uint16_t* memory);
int My_puts(const char* string);


#ifdef __cplusplus
}
#endif
 
#endif
