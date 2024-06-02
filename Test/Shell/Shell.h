#ifndef SHELL_H
#define SHELL_H

//Loading the stuff we need, all the commands we want to make
void load_shell();

//clearing the screen !!
void refreshShell();

//getting the command the user has given.
void parseCommand();


void setUpShell();

void resetBuffer();

#endif