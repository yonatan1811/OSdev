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


bool StringStartsWith(const char* s, const char* t){
    const char* g = t;
	
	bool res = true;
	int i = 0;
	do{
		if(s[i] != t[i] || i > 80){
			res = false;
			break;
		}
		else i++;
	}while(g[i] != 0);
	return res;
    
}


void strip(char* strDest , const char* strSrc)
{
	int i =0;
	int j =0;
	for(i = 0 ; i < strlen(strSrc) ; i ++)
	{
		if(*(strSrc + i) != ' ')
		{
			*(strDest + j) = *(strSrc + i);
			j++;
		}

	}
}


int count(char* string , char tav)
{
	int i = 0;
	int count = 0;
	for(i = 0 ; i < strlen(string) ; i ++)
	{
		if(*(string + i) == tav)
			count ++;
	}
	return count;
}

bool equal(const char* str , const char* str2)
{
	if(strlen(str) != strlen(str2))
		return false;

	int i = 0;
	for(i = 0 ; i < strlen(str) ; i ++)
	{
		if(*(str + i) != *(str2 +i))
			return false;
	}
	return true;
}