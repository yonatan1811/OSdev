#ifndef PAGING_H
#define PAGING_H
#include "../Utils/Typedefs.h"

/*
* So how paging works? the main idea is to divide the memory into chunks/ blocks. if we want to have 1 table of memory and each row will point
* at one address we will have a table of 2^32 rows. which is not okay. so what can we do? we are going to have a directory a.k.a page_directory
* which is going to be 2^10 in size. when we will see an address like this : 0x00000000100000 the first 10 bits will be the page directory number.
* so we can know to which directory number we need to access. the next thing in the architecture is the page table. each row in the page directory
* points at a different page table, the page table is represented in the next 10 bits of the address. and for the last 12 bits is the offset!!
* horrayyyy, we can now code:
*/

#define BLOCK 0x1000 // 4096 bytes .


//some enums for easy work

typedef enum
{
	PD_PRESENT         = 0b1,
	PD_READWRITE       = 0b10
}PD_FLAGS;

typedef enum 
{
	PT_PRESENT         = 0b1,
    PT_READWRITE       = 0b10
}PT_FLAGS;


//this function will make all the next functions work together. the first function to enalbe paging. will be called from the kernel
void init_paging(unsigned int* page_directory , unsigned int* first_page_table);


void* get_virtual_address(int pd_index , int pt_index , int offset); //pd_index , the page directory number, pt_index the page table number, and the offset.

void add_page(unsigned int* page_directory , unsigned int* page_table , int index , int offset , PT_FLAGS ptf , PD_FLAGS pdf);

void init_page_directory(unsigned int* page_directory);


#endif



