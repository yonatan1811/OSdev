#include "../include/string.h"

/*
	strlen - a funtction used to know what's the string length.
	input - char* , a string to check
	output - the length itself.
*/

const char* reverse(const char* str, char* buffer, int len)
{
	int i;
	for (i = 0; i <= len; i++){
		buffer[i] = str[len - 1 - i];
	}
	buffer[i] = '\0';
	return buffer;
}

size_t strlen(const char* string) 
{
	size_t len = 0;
	int i = 0;
	while(string[i] != '\0') // while we didnt reach the EOF
	{
		len += 1;
		i++;
	}
	return len; 
}

char* strcpy(char* strDest , const char* strSrc)
{
	char* temp = strDest;
	while((*strDest++ = *strSrc++) != '\0');
}
