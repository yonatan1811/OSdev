#ifndef _STRING_H
#define _STRING_H 1
 
#include "cdefs.h"
 
#include "stddef.h"
#include "../Utils/Typedefs.h"
 
#ifdef __cplusplus
extern "C" {
#endif

const char* reverse(const char* str, char* buffer, int len);

size_t strlen(const char* string);

char* strcpy(char* strDest , const char* strSrc);

bool StringStartsWith(const char* s, const char* t);

void strip(char* strDest , const char* strSrc);

int count(char* string , char tav);

bool equal(const char* str , const char* str2);

#ifdef __cplusplus
}
#endif
 
#endif
