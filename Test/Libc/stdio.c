#include "../include/stdarg.h"
#include "../include/stdio.h"
#include "../include/terminal.h"


#define BUFF_SIZE 1024
#define MEM (uint16_t*)0xb8000

const char g_hexChars[] = "0123456789abcdef"; //16 chars for hex


int My_putchar(int int_char , uint16_t* memory)

{
	if ((char)int_char == '0')
	{
		return -1;
	}

	char c = (char)int_char; //convert the char from int to char
	tty_putchar(memory , c); //writes the char
	return int_char;//just returns the char	

}


//this function will help us print hex
void printf_ui(size_t number , int radix) // might cause some problems
{
	char buffer[32];
	int pos = 0;

	do //conver number to ascii:
	{
		size_t rem = number % radix;
		number = number / radix;
		buffer[pos++] = g_hexChars[rem];
	}while (number > 0);

	while(--pos >=0)
		My_putchar(buffer[pos] , MEM);
}



int My_printf(const char* restrict format , ...)
{
	va_list args; // starts a new list to manage the variable arguments
	int counter =0; //keep track of how many characters were written
	char buffer[BUFF_SIZE];
	int buffer_index = 0;


	va_start(args , format); // declares the start of the list , gives a pointer to the start of the list
	while(*format) // while the list isn't over
	{
		const char* format_begun_at = format;
		if(*format == '%')
		{
			format++; // getting the next variable in the list;
			if (*format == '%') // if we want to print the char '%' we need a special case for that
			{
				My_putchar((int)'%' , MEM);
				counter++;
			}
			else if(*format == 'c') // a case for a char
			{
				char ch = va_arg(args , char);
				My_putchar(ch , MEM);
				counter++;
				break;
			}
			else if(*format == 's') // a case for string
			{
				char* str = va_arg(args , char*);
				for (int i = 0; i < strlen(str); ++i)
				{
					My_putchar(str[i] , MEM);
					counter++;
				}
			}

			else if(*format == 'd' || *format == 'i') // a case for an integer / long
			{
				int num = va_arg(args , int);
				print_integer(num , MEM);
				counter++;
			}

			else if(*format == 'X' || *format == 'x' || *format == 'p')
			{
				printf_ui(va_arg(args , unsigned long) , 16);
			}

			else if(*format == 'u')
			{
				printf_ui(va_arg(args , unsigned int) , 10);
			}

		}
		else // in case there is no % and just a regular print f without nothing
		{
			size_t len = strlen(format_begun_at);
			if(BUFF_SIZE < len)
				return -1;
			for (int i = 0; i < len; i++)
			{
				My_putchar(format_begun_at[i] , MEM);
				counter++;
			}

			format+=len;

		}

		*format++; // move to the next character in the format string
	

	}



	va_end(args);
	return counter	;


}


int My_puts(const char* string)
{
	return My_printf("%s" , string); // just a simple print for a string
}
