#ifndef BITMAP_H
#define BITMAP_H
#include "Typedefs.h"

//this file will define our bitmap.

typedef unsigned char* bitmap_t; // our bitmap we can use to control our memory.

void set_bitmap(bitmap_t b , int i );

void unset_bitmap(bitmap_t b, int i);

char get_bitmap(bitmap_t b , int i);

bitmap_t create_bitmap(void* loc , int n);

#endif