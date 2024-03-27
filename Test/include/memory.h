#ifndef MEMORY_H
#define MEMORY_H
#include "../Utils/Typedefs.h"

//   **this file will be used to manage the memory (RAM)
void* memset(void* dest, unsigned char val, size_t count); // a function that will put some data in the requsted dst

//   **this function will copy from the source to the dest
void memcp(void* source, void* dest, size_t count);


//this will compare between two pointer / data and will tell if the data is identical else no. 
//output : 0 for identical . 1 if the dest is "bigger" then the source. -1 if source is bigger then dest
int memcmp(const void* dest , const void* source, size_t count);

void* memmove(void* dstptr,  void* srcptr, size_t size);


#endif