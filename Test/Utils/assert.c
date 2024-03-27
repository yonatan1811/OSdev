#include "../Drivers/VGA_Text.h"
#include "../include/stdio.h"
#include "colors.h"

extern char ker_tty[4000];

void assert(int condition){
    if(!condition){
        //clear_tty(ERROR_COLOR, ker_tty);
        //display_tty(ker_tty);
        //SetCursorPosRaw(0);
        
        My_printf("assert failed");
    }
}
