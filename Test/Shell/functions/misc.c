
#include "../../Utils/Typedefs.h"
#include "../../include/terminal.h
#define FDEF(name) void name(const char* s)



FDEF(hcf)
{
	int x = *((uint8_t*) 0xffffffff) = 1;
}

FDEF(color)
{
	int forground = (int)(s[6] - '0');
	int background = (int)(s[7]-'0');
	colorTerminal(forground , background);
}