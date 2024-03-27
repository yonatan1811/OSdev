#ifndef PMM_H
#define PMM_H
#include "../Utils/Typedefs.h"


//the whole point of Memory managing , we will have a bit map that the first bit of the block will tell wether the block is allocated or not.
//still wondering what's the point of life.





typedef struct {
    uint16_t lower_size;
    uint16_t upper_size;
} mem_t;

typedef uint32_t physical_addr; // a way to represent the physical_address
#define FREE_MEM 0x100000
#define BLOCK 4096



mem_t upper_memget (void);

//this function will initiate the memory.
void    pmmngr_init (size_t memSize, physical_addr bitmap);
void    pmmngr_init_region (physical_addr base, size_t size);
void    pmmngr_deinit_region (physical_addr base, size_t size);
void*   pmmngr_alloc_block ();
void    pmmngr_free_block (void* p);

/*


the core function of the kernel. lets the kernel allocate memory.
*  input  - size_t size - how many bytes the user needs?
*  output - void* , a pointer to the address.
*/

	




#endif
