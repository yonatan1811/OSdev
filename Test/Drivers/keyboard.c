#include "keyboard.h"
#include "../Utils/Typedefs.h"
#include "../Utils/Conversions.h"
#include "../Utils/port_io.h"
#include "../CPU/irq.h"
#include "../include/stdio.h"
#include "../Shell/Shell.h"
#include "../include/terminal.h"


/********************FUNCTIONS*********************
* kb_install: installs keyboard IRQ handler       *
* keyboard_handler: handles interrupt requests    *
**************************************************/

extern int curMode;					// CURRENT MODE



const char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};




enum scan_codes 
{
    LEFT_ARROW_PRESSED = 0x4b,
    RIGHT_ARROW_PRESSED = 0x4d,
    DOWN_ARROW_PRESSED = 0x48,
    UP_ARROW_PRESSED = 0x50,
    LEFT_SHIFT_PRESSED = 0x2a,
    CAPS_LOCK_PRESSED = 0x3a,
    RETURN_PRESSED = 0x1c,
    F5_PRESSED = 0x3f,

    LEFT_SHIFT_RELEASED = 0xaa
};

void keyboard_handler(struct regs *r)
{
    /* static prevents these variables from being reassigned back to false after the function returns and gets called again
    * and it keeps the variables local to this function */
    static bool shift_pressed = false;
    static bool caps_lock = false;

    unsigned char scancode;

    scancode = inb(0x60);
    if (scancode & 0x80)
    {
        //see if the user realesed the shift key , alt key , esc etc
        // switch(scancode)
        // {
        //     case LEFT_SHIFT_RELEASED: shift_pressed = false; break;
        // }
    }

    else
    {
        switch(scancode)
        {
            case LEFT_SHIFT_PRESSED: shift_pressed = true; break;
            case CAPS_LOCK_PRESSED: caps_lock = !caps_lock; break;

            default : 
                char c = kbdus[((int)scancode)%128];
                if (c == '\b')
                    deleteCol();
                else if (c == '\n')
                {
                    parseCommand();
                    if(c == ']')
                    {
                        My_putchar('*',(uint16_t*)0xb8000);
                    }
                    else if(c == '[')
                    {
                        My_putchar('+',(uint16_t*)0xb8000);
                    }
                    else
                      My_putchar(c , (uint16_t*)0xb8000);
                }
                else
                {
                    if(c == ']')
                    {
                        My_putchar('*',(uint16_t*)0xb8000);
                    }
                    else if(c == '[')
                    {
                        My_putchar('+',(uint16_t*)0xb8000);
                    }
                    else
                      My_putchar(c , (uint16_t*)0xb8000);
                }
        }

    }

    

}
void kb_install()
{
	irq_install_handler(1, keyboard_handler);
}