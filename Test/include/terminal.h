#ifndef TERMINAL_H
#define TERMINAL_H
 
#include "stddef.h"
#include "../Utils/Typedefs.h"
 


void terminal_initialize(uint16_t* memory); // to initialize the terminal so we could reset the courser.
void terminal_write(const char* data, size_t size , uint16_t* memory); // a function that could write a whole string
void terminal_writestring(const char* data , uint16_t* memory); // a function that will write a string
void print_integer(int value , uint16_t* memory);//this function will help us print an integer when we have %d
void setCursorPos(int row , int col);// includes also row and col
void deleteCol();
void deletRow(int row);
void colorTerminal(uint8_t forground , uint8_t background);

#endif