#include "../include/memory.h"
#include "../Memory/paging.h"
#include "kernel.h"
#include "../include/terminal.h"
#include "../include/string.h"
#include "../include/stdio.h"
#include "../Memory/PMM.h"
#include "../Memory/VMM.h"
#include "../Memory/heap.h"
#include "../Drivers/disk.h"
#include "../Drivers/keyboard.h"
#include "../CPU/idt.h"
#include "../CPU/gdt.h"
#include "../CPU/irq.h"
#include "../CPU/isr.h"

#define MEMORY (uint16_t*)0xB8000

/*
stdio.c functions : 
My_printf
My_puts
*/



//page directory for the init paging
unsigned int page_directory[1024] __attribute__((aligned(4096)));
unsigned int first_page_table[1024] __attribute__((aligned(4096)));
unsigned int second_page_table[1024] __attribute__((aligned(4096)));

PD_FLAGS page_directory_flags = PD_PRESENT + PD_READWRITE;
PT_FLAGS first_page_table_flags = PT_PRESENT + PT_READWRITE;


#define FREE_MEM 0x100000
#define START_FREE_MEM 0x100000

void main ()
{

    uint16_t* mem = (uint16_t*)MEMORY;

    //terminal is being initialized!!!!
    terminal_initialize(mem);

    init_paging(page_directory , first_page_table);
    add_page(page_directory, second_page_table, 1, 0x1000000, page_directory_flags, first_page_table_flags);

    GDT_Init();
    idt_install();
    isrs_install();
    irq_install();
    kb_install();
    __asm__ volatile ("sti");

    //debug:
    pmmngr_init(START_FREE_MEM , FREE_MEM);
    init_bitmap((bitmap_t) 0x100000, 10000);//starting at address 0x400000 and giving a length of 10000 bytes
    set_dynamic_mem_loc (0x100000 + 10000/2); //setting our dynamic location at 0x400000 + 5000

    set_bitmap(get_allocation_bitmap(), 8);     // first fit algo check

    //actual code : 
    My_puts("Hi guys, and welcome to Lukach operating system!\n");

    setUpShell();
}



