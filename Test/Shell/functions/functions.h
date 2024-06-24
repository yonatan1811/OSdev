#ifndef SHELLFUNCTIONS2_H
#define SHELLFUNCTIONS2_H

// Function header to simplify declaring shell commands
#define FHDR(name) void name(const char* s);


// text.c
FHDR(echo); // echo a string to the screen
FHDR(clear);
FHDR(calc);

//memory.c
FHDR(meminfo);

//misc.c
FHDR(hcf);
FHDR(color);

#endif