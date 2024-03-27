#ifndef STACK_H
#define STACK_H
#include "Typedefs.h"
#include "../include/stdio.h"
	
/*
* this file will be used to implement the stack which will be used in the memory allocation.
*/

#define LIMIT 200 //200 blocks can be used , each block in the size of 4096
#define BLOCK 4096 

typedef struct stack
{
	long top;
	unsigned int* stack_mem;

} stack;



#endif