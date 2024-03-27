//this file will be our file to define some constant variables.

#ifndef TYPEDEF_H
#define TYPEDEF_H


typedef unsigned char uint8_t; //a single char is one byte. so we can define it as uint8_t.
typedef unsigned short uint16_t; //in 32 bit computers. the int is 16 bit long.
typedef unsigned int uint32_t; 
typedef unsigned long size_t; // same as 64 bit.

typedef uint8_t bool;
#define true    1
#define false   0


#define NULL (void*)0

typedef int maybe_void;
typedef int maybe_int;

#endif
