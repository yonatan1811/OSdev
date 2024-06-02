#include "../Utils/Typedefs.h"
#include "../include/stdio.h"
#include "../include/string.h"
#include "shellFunctions.h"
#include "../include/memory.h"
#include "../Utils/Conversions.h"
#include "../include/terminal.h"


#define defultPosRow 20
#define defaultPosCol 0

#define VGA_Width  80
#define VGA_Height 25

#define MEM (char*)0xb8000


int row = 1;
int col = 0;

int CommandCursor;


const char* currentTask;

void refreshShell(){
    deletRow(defultPosRow);
    setCursorPos(defultPosRow, 0);
// 	My_puts("LukachOS shell - [");
//     My_puts("task: ");
//     My_puts(currentTask);
//     My_puts(" | ");
//     My_puts("dir: -");
//     My_puts("]\n");
// 	return;
}


char CommandBuffer[128];
char commandTemp[128];
void findCommand(){
    setCursorPos(defultPosRow, 0);
	int i = 0;
    int j = 0;
    for (int i = 42 * VGA_Width -2; i < 42*VGA_Width + 78 ;i+=2 , j++)
    { // some really black magic
        commandTemp[j] = *(MEM + i);
    }
	commandTemp[j] = 0;
    strip(CommandBuffer , commandTemp);

    
}


void parseCommand()
{
    findCommand();
    setCursorPos(row , col);
    if (CommandBuffer[0] == 0){;} // if we cant find any commands
    else
    {
        shellfunction* cmd  = TryGetCMD(CommandBuffer);
        if (cmd!= 0)
        {
            cmd->fptr(CommandBuffer);
            if(StringStartsWith(CommandBuffer , "clear") == true)
            {
                row = 0;                
            }
            else if (StringStartsWith(CommandBuffer , "help") == true)
            {
                row +=7 ;
                
            }
            else
            {
                row +=1;
            }
            col =0;
        }
        else
        {
            My_puts("\"");
            My_puts(CommandBuffer);
            My_puts("\" is not a command ;) ");
            row +=1;
            col =0;
        }
    }

    refreshShell();
    resetBuffer();

}

//we can attend to this function in two ways . i'll do the hard code way
void resetBuffer()
{
    int i = 0;
    for(i = 0; i < 128 ; i ++)
    {
        CommandBuffer[i] = 0;
        commandTemp[i] = 0;
    }
}

void setUpShell()
{
    setCursorPos(defultPosRow+1 , 0); // default place

}