#include "../include/terminal.h"
#include "../include/vga.h"

#include "../include/stdbool.h"
#include "../include/stddef.h"
#include "../include/string.h"
//#include "../Utils/Typedefs.h"

//some constants for the terminal size

#define VGA_Width  80
#define VGA_Height 25

static int col = 0;
static int row = 1;

#define MEM (uint16_t*)0xb8000

void tty_putchar(uint16_t* mem , unsigned char c )
{
	if(c == '\n')
	{
		row +=1;
		col = 0;
	}
	else
	{
		*(mem + row*VGA_Width + col) = vga_entry(c, vga_entry_color(VGA_COLOR_GREEN , VGA_COLOR_BLACK));
    	col ++;	
	}
    
}


 void print_integer(int value , uint16_t* memory)//this function will help us print an integer when we have %d
 {
 	char buffer[32];  //Buffer to store the string representation
     int printed = 0;  //Counter for the number of characters printed
     int save = 0;

     if(value < 0)  //a negetive number 
     {
     	tty_putchar( memory,('-'));
     	printed++;
     	value = -value;
     }

     do 
     {
     	buffer[save++] = '0' + (value%10);
     	value/=10;
     	printed++;
     } while	(value	>0 ); //just a simple convertion of string to int

     for (int i = save=1; i >=0; i--)
     {
     	tty_putchar(memory , buffer[i]);
     }

     return printed;
 }



void terminal_initialize(uint16_t* memory) // to initialize the terminal so we could reset the courser.
{
	row = 0;
    col = 0;
    for (int i = 0; i < VGA_Height; ++i)
    {
        for (int j = 0; j < VGA_Width; ++j)
        {
            *(memory + i*VGA_Width + j) = vga_entry(' ' , vga_entry_color(VGA_COLOR_GREEN , VGA_COLOR_BLACK));
        }
    }

    // print_integer(row , memory);
    // print_integer(col , memory);


}






//a simple function to write a whole string
void terminal_write(const char* data, size_t size , uint16_t* memory) // a function that could write a whole string
{

	for (size_t i = 0; i < size; i++)
    {
        tty_putchar(memory , *(data+i));

    }

}

void terminal_writestring(const char* data , uint16_t* memory)
{
	terminal_write(data, strlen(data) , memory);
}





void setCursorPos(int rowToSet , int colToSet)  // includes also row and col
{
    col = colToSet;
    row = rowToSet;
}   

void deleteCol()
{
    *(MEM + row*VGA_Width +col -1) = vga_entry(' ' , vga_entry_color(VGA_COLOR_GREEN , VGA_COLOR_BLACK));
    col = col -  1;
}

void deletRow(int rowToSet)
{
    int i =0;
    for(i =0; i < VGA_Width ; ++i)
    {
        *(MEM + (rowToSet+1)*VGA_Width + i) = vga_entry(' ' , vga_entry_color(VGA_COLOR_GREEN , VGA_COLOR_BLACK));

    }
}

void colorTerminal(uint8_t forground , uint8_t background)
{
	for (int i = 0; i < VGA_Height; ++i)
    {
        for (int j = 0; j < VGA_Width; ++j)
        {
            *(memory + i*VGA_Width + j) = vga_entry(' ' , vga_entry_color(forground , background));
        }
    }
}
