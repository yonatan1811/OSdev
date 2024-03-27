#include "../Memory/PMM.h"
#include "../include/stdio.h"
#include "../include/memory.h"


/*
* some PMM.h defines:
* FREE_MEM - a permenent address that is used to save the start of the memory we can use
* BLOCK - a single block so we have control on every free and used blocks
*/

//! 8 blocks per byte
//because we have 8 in a byte, so one block per bit 
#define PMMNGR_BLOCKS_PER_BYTE 8
 

 //4096 bytes for each block
//! block size (4k)
#define PMMNGR_BLOCK_SIZE   4096
 
//! block alignment
#define PMMNGR_BLOCK_ALIGN  PMMNGR_BLOCK_SIZE

//! size of physical memory
static  uint32_t    _mmngr_memory_size=0;
 
//! number of blocks currently in use
static  uint32_t    _mmngr_used_blocks=0;
 
//! maximum number of available memory blocks
static  uint32_t    _mmngr_max_blocks=0;
 
//! memory map bit array. Each bit represents a memory block
static  uint32_t*   _mmngr_memory_map= 0;

//uint32_t memSize = 0x100000;

/*
some defines for the start of the memory
*/

//memory block = page 


//inteface functions:
size_t  pmmngr_get_memory_size ();
unsigned int pmmngr_get_block_count ();
unsigned int pmmngr_get_use_block_count ();
unsigned int pmmngr_get_free_block_count ();
unsigned int pmmngr_get_block_size ();




mem_t upper_memget()
{
    mem_t* mem = (mem_t*)0x8100;
    return *mem;
}




//This function is used to find the first free block. the whole conecpt is to check each dd instead of db so the check will be faster 
int mmap_first_free () {

        //! find the first free bit
        for (unsigned int i=0; i< pmmngr_get_block_count() /32; i++)
                if (_mmngr_memory_map[i] != 0xffffffff)
                        for (int j=0; j<32; j++) {                              //! test each bit in the dword

                                int bit = 1 << j;
                                if (! (_mmngr_memory_map[i] & bit) )
                                        return i*4*8+j;
                        }

        return -1;
}


//getting to the real stuff:
/*
  in here we are going to get real physical and will really go down and deep:
  the mem size is the number of free memory we got from the boot loader, in my case it will be a magic number until i figure out how to get the real size
  the bit map , our structure that will help us to keep track of the free blocks.
  the number of blocks. the memory size divided by the size of 1 block
  and we will be setting the memory as all of it is used
*/
void	pmmngr_init (size_t memSize, physical_addr bitmap) {
 
	_mmngr_memory_size	=	memSize;
	_mmngr_memory_map	=	(uint32_t*) bitmap;
	_mmngr_max_blocks	=	(memSize*1024) / PMMNGR_BLOCK_SIZE;
	_mmngr_used_blocks	=	0;
 
	//! By default, all of memory is in use
	memset (_mmngr_memory_map, 0xf, pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE );
}

void	pmmngr_init_region (physical_addr base, size_t size) {
 
	int align = base / PMMNGR_BLOCK_SIZE;
	int blocks = size / PMMNGR_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_unset (align++);
		_mmngr_used_blocks--;
	}
 
	mmap_set (0);	//first block is always set. This insures allocs cant be 0
}

void	pmmngr_deinit_region (physical_addr base, size_t size) {
 
	int align = base / PMMNGR_BLOCK_SIZE;
	int blocks = size / PMMNGR_BLOCK_SIZE;
 
	for (; blocks>0; blocks--) {
		mmap_set (align++);
		_mmngr_used_blocks++;
	}
}


void*	pmmngr_alloc_block () {
 
	if (pmmngr_get_free_block_count() <= 0)
		return 0;	//out of memory
 
	int frame = mmap_first_free ();
 
	if (frame == -1)
		return 0;	//out of memory
 
	mmap_set (frame);
 
	physical_addr addr = frame * PMMNGR_BLOCK_SIZE;
	_mmngr_used_blocks++;
 
	return (void*)addr;
}

void	pmmngr_free_block (void* p) {
 
	physical_addr addr = (physical_addr)p;
	int frame = addr / PMMNGR_BLOCK_SIZE;
 
	mmap_unset (frame);
 
	_mmngr_used_blocks--;
}




//interface function : 


size_t  pmmngr_get_memory_size () {

        return _mmngr_memory_size;
}

unsigned int pmmngr_get_block_count () {

        return _mmngr_max_blocks;
}

unsigned int pmmngr_get_use_block_count () {

        return _mmngr_used_blocks;
}

unsigned int pmmngr_get_free_block_count () {

    return _mmngr_max_blocks - _mmngr_used_blocks;
}

unsigned int pmmngr_get_block_size () {

        return PMMNGR_BLOCK_SIZE;
}



//a function to set a bit to 1, because we are dealing with bits and not with integers we are converting this integer to a bit 
//and using this as an index
inline void mmap_set (int bit) {
 
  _mmngr_memory_map[bit / 32] |= (1 << (bit % 32));
}


//same as above, instead of setting, unsetting. 1->0
inline void mmap_unset (int bit) {
 
  _mmngr_memory_map[bit / 32] &= ~ (1 << (bit % 32));
}


//testing the bit, true if the bit is 1 else 0
inline bool mmap_test (int bit) {
 
 return _mmngr_memory_map[bit / 32] &  (1 << (bit % 32));
}








