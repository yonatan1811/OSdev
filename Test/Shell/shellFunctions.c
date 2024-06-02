#include "../Utils/Typedefs.h"
#include "../include/memory.h"
#include "../include/stdio.h"
#include "../Utils/Conversions.h"
#include "../include/string.h"
#include "../Shell/Shell.h"

#include "shellFunctions.h"
#include "./functions/functions.h"


extern const char* currentTask;


#define CMDENTRY(fptr, alias, help, usage) {    \
    fptr,                                       \
    alias,                                      \
    help,                                       \
    usage                                       \
}


void helpCMD(const char* s);





//all the function we will be able to handle
shellfunction CMDs[] = {
    CMDENTRY(&helpCMD,  "help",     "Shows command list", "help"),
    CMDENTRY(&echo,     "echo",     "Prints text", "echo [text]"),
    CMDENTRY(&clear,    "clear",    "Clears the screen", "clear"),
    CMDENTRY(&hcf,      "hcf",      "Crashes your system", "hcf"),
    CMDENTRY(&meminfo,  "meminfo",  "Shows memory info", "meminfo"),
    CMDENTRY(&calc,     "calc" ,    "shows the calc output of ", "calc")
    //CMDENTRY(&diskinfo,  "diskinfo",  "Shows disk info", "diskinfo") we will put this for later.

};



void helpCMD(const char* s){
    currentTask = "help";
    My_puts("List of commands:\n");
    for(int i = 0; i < sizeof(CMDs)/sizeof(shellfunction); i++) {
        My_puts("   ");
        My_puts(CMDs[i].usage);
        My_puts(": ");
        My_puts(CMDs[i].help);
        My_puts("\n");
    }
    // else{
    //     My_puts("Invalid option: \"");
    //     if(s[0] == ' ') My_puts((const char*)((int)s + 1));
    //     else My_puts(s);
    //     My_puts("\"");
    // }
   
}



shellfunction* TryGetCMD(char* cmdbuf){
    for(int x = 0; x < sizeof(CMDs)/sizeof(shellfunction); x++){
        if(StringStartsWith(cmdbuf, CMDs[x].alias)){
            return &CMDs[x];
        }
    }
    return 0;
}
