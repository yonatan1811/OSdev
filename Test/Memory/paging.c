#include "paging.h"
#include "paging_utils.h"

void init_page_directory(unsigned int* page_directory)
{
	//a simple function to inint the page_directory
	for (int i = 0; i < 1024; ++i)
	{
		page_directory[i] = 0x0000000000 | 2; //xoring here last bits will be 010 , first 0 - only supervisor can access , 1 - the page is read/write , 0 - isn't present
	}
	//returns nothing
}



//this function will add a page into the page table
void add_page(unsigned int* page_directory , unsigned int* page_table , int index , int offset , PT_FLAGS ptf , PD_FLAGS pdf) 
{
	for (int i = 0; i < 1024; ++i)
	{
		page_table[i] = offset + (i*BLOCK) | pdf;
	}

	page_directory[index] = ((unsigned int)page_table) | pdf; //adding the new page table into the page directory

}

void init_paging(unsigned int* page_directory , unsigned int* first_page_table)
{
	init_page_directory(page_directory);

	//these flags will be useful when we are adding a page to the page table
	PD_FLAGS pdf = PD_PRESENT + PD_READWRITE;
    PT_FLAGS fpf = PT_PRESENT + PT_READWRITE;

    add_page(page_directory , first_page_table , 0 , 0 , fpf , pdf);

    //inintiating the paging in asm:
    loadPageDirectory(page_directory);
    enablePaging();
}