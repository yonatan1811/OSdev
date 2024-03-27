#pragma once
#include "../Utils/Typedefs.h"
#include "../Memory/VMM_Help.h"

//okay so here we will have some few defines and variables.
//we will go one by one so it will be understandble and okay. (:
 
//! virtual address
//this address will represent the virtual address adn we will make the convertions on it.
typedef uint32_t virtual_addr;
 
//in x86 architecture the page directory has 1024 entries also for the page table. the page directory actually has 1024 page table entries.
//although in the page table we have 1024 entries, and each entry is a page.
#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIR	1024

//these are macros that just returns the respective partion of a virtual address. 
#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3ff)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3ff)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xfff)

//! page table represents 4mb address space
#define PTABLE_ADDR_SPACE_SIZE 0x400000

//! directory table represents 4gb address space
#define DTABLE_ADDR_SPACE_SIZE 0x100000000

//! page sizes are 4k
#define PAGE_SIZE 4096
 
//! page table
struct ptable_t {
 
	pt_entry m_entries[PAGES_PER_TABLE];
}typedef ptable;
 
//! page directory
struct pdirectory_t {
 
	pd_entry m_entries[PAGES_PER_DIR];
}typedef pdirectory;


//getting to the real stuff

//allocating a frame- page in the physical address space
bool vmmngr_alloc_page (pt_entry* e);


//getting rid of a page from our page table and freeing the frame in the physical memory manager
void vmmngr_free_page (pt_entry* e);


//this function is very important for us. we are going to get an address , and convert it to a page entry, or in other words. a page.
inline pt_entry* vmmngr_ptable_lookup_entry (ptable* p,virtual_addr addr);

//same as above, but this time for the page directory, this will return a page table.
inline pd_entry* vmmngr_pdirectory_lookup_entry (pdirectory* p, virtual_addr addr);
