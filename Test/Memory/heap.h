#ifndef HEAP_H
#define HEAP_H

#include "../Utils/bitmap.h"



/*
my concept of heap:
that's one way:

having a header will keep track of all the blocks, exactly like the physical memory manager and the virtual memory manager. this time we are going to
only give a size as a parameter. our malloc will use the block we got from the vmm to give it to the user.

So, the idea is to take a header. which will specify size , a pointer (an address) , and a "next" pointer. so for example we are going to have something like that:

size - 4096 - 1 block
pointer - an address of the memory.
next pointer, if we had more than one block we need to know how many blocks are the user's


so when we are reciving a pointer to free from the user we know how many blocks to free via the header.

second way and more efficient: bitmap!
so the idea is to have a bit map that stores idea of each block. a bitmap is an array of bits. in our case our bit map is going to be a unsigned char.
that means that each cell will present one byte.


*/


/*
This function will be used to initialize the bitmap. we will give it an addres. and length.
input : int length. the length of our bitmap. uint32 loc. an address.
output: none.
*/
void init_bitmap (bitmap_t loc, int length);


/*
This function will translate our physical memory into the dynamic one.

*/
void set_dynamic_mem_loc (void *loc);



//kernel malloc !!!
/*
giving blocks to the user to use mid-run 
input : size_t size , number of bytes
output: an address!!
*/
void *kmalloc (size_t size);

/*
the opposite of malloc. we will free blocks that are in the user's control

*/
int kfree(void* loc, size_t size);

bitmap_t get_allocation_bitmap();

int getBitSize();
#endif
