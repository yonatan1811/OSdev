#ifndef _STRING_H
#define _STRING_H 1
 
#include "cdefs.h"
 
#include "stddef.h"
 
#ifdef __cplusplus
extern "C" {
#endif

const char* reverse(const char* str, char* buffer, int len);

size_t strlen(const char* string);

char* strcpy(char* strDest , const char* strSrc);


#ifdef __cplusplus
}
#endif
 
#endif
