#include "timer.h"



//we dont have interrupts for now so we are using just a regular while loop.
void sleep(int seconds)
{
	int start = 0;
	while(start < seconds)
	{start++;}
	return;
}