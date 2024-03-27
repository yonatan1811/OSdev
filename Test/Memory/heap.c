#include "heap.h"

#define MAX_BLOCKS 100

//some globals to have to use the bitmap

volatile bitmap_t allocation_bitmap = NULL;

volatile int bitmap_size = 0;

volatile void *dynamic_mem_loc = NULL;


// in the kernel we will use this to see if we are going in the right direction.
bitmap_t get_allocation_bitmap (){
    return allocation_bitmap;
}

//getting to the real stuff here. we are going to make a dynamic memory here. let's hop in.


void init_bitmap (bitmap_t loc, int length)
{
	allocation_bitmap = create_bitmap(loc, length); //creating a bitmap used in the bitmap.h
    bitmap_size = length; // nothing special.
}

void set_dynamic_mem_loc (void *loc)
{
	dynamic_mem_loc = loc;
}


//first fit allocation.
void *kmalloc (size_t size)
{
	int contiguous = 0;
    int current_champion = 0;
    for (int i = 0; i < bitmap_size; i++){
        
        if (contiguous == 0) current_champion = i;
        
        if (get_bitmap(allocation_bitmap, i) == 0) contiguous++;
        if (get_bitmap(allocation_bitmap, i) == 1) {
            contiguous = 0;
            continue;
        }
        
        if (contiguous >= size){
            
            for (int j = current_champion; j < current_champion + size; j++){
                set_bitmap(allocation_bitmap, j);
            }
            
            return (void*) (current_champion + (int)dynamic_mem_loc);
        }
    }
    return NULL;
}


int kfree(void* loc, size_t size){     // also size as input, more practical to implement this way
    
    int bitmap_index = (int) loc - (int) dynamic_mem_loc;
    
    if (bitmap_index > bitmap_size || bitmap_index < 0)
        return -1;
        
    if (bitmap_index + size > bitmap_size)
        return -2;
    
    for (int i = bitmap_index; i < bitmap_index + size; i++){
        unset_bitmap(allocation_bitmap, i);
    }
    return 0;
}
