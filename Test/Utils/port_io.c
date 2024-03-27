#include "port_io.h"


//https://wiki.osdev.org/Inline_Assembly/Examples


void outb(uint16_t port, uint8_t data)
{
	__asm__ volatile("outb %0, %1" 
		: 
		: "a"(data)  
		, "Nd"(port)
		:
		);
	return;
}

uint8_t inb(uint16_t port)
{
	uint8_t res;
	__asm__ volatile("inb %1, %0" 
		: "=a"(res) 
		: "Nd"(port)
		:
		);
	return res;
}

void outl(uint16_t port, uint32_t value){
	__asm__ volatile ("outl %%eax, %%dx" 
		: 
		: "d" (port), "a" (value)
		: );
}


uint16_t inw(uint16_t port){
   uint16_t ret;
   __asm__ volatile ("inw %1, %0" 
   	: "=a" (ret) 
   	: "dN" (port)
   	: );
   return ret;
} 