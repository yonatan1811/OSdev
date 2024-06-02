#include "../../Memory/heap.h"
#include "../../include/stdio.h"

#define FDEF(name) void name(const char* s)

FDEF(meminfo)
{
	My_puts("Memory used : ");
	int size = getBitSize();
	My_printf("%d" , size);
	My_puts(" Bytes");
	My_puts("\n");
}

