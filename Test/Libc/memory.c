#include "../include/memory.h"


void* memset(void* dest, unsigned char val, size_t count) // a function that will put some data in the requsted dst
{
	//char* buffer = "Yonatan ha hatih";

	//if this pointer isn't a real pointer;
	if(!dest)
		return -1;


	unsigned char* destC = (unsigned char*)dest;
	int i = 0;
	for (i = 0; i < (int)count; ++i)
	{
		*(destC + i) = val;
	}

	return dest;
}


void memcp(void* source, void* dest, size_t count)
{
	if(!dest || !source) // if one of them is null
		return -1; // error


	unsigned char* destC = (unsigned char*)dest;
	unsigned char* sourC = (unsigned char*)source;

	for (int i = 0; i < count; ++i)
	{
		destC[i] = sourC[i];
	}

	//no return here.

}


//this will compare between two pointer / data and will tell if the data is identical else no. 
//output : 0 for identical . 1 if the dest is "bigger" then the source. -1 if source is bigger then dest

int memcmp(const void* dest , const void* source, size_t count)
{
	if(!dest || !source) // if one of them is null
		return -1; // error


	unsigned char* destC = (unsigned char*)dest;
	unsigned char* sourC = (unsigned char*)source;

	for (int i = 0; i < count; ++i)
	{
		if(destC[i] > sourC[i])
			return -1; // if the destination is "bigger" than the source we will return -1
		else if(destC[i] < sourC[i])
			return 1; //else we will return the value 1
	}
	return 0;

}


// a safer way to move data from source to its dest
void* memmove(void* dstptr, void* srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}