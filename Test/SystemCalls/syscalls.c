#include "../CPU/idt.h"
#include "../Drivers/VGA_Text.h"
#include "../include/stdio.h"
#include "syscalls.h"

int syscall_stub (regs *r, int number){
    switch (number) {
        case 1:
            //sys_exit
            return sys_exit(r);
            
        case 2:
            //sys_fork
            return sys_fork(r);
        case 3:
            //sys_read
            return sys_read(r);
        case 4:
            //sys_write
            return sys_write(r);
        case 5:
            //sys_open
            return sys_open(r);
        case 6:
            //sys_close
            return sys_close(r);
    }
}


int sys_exit (regs *r){
     My_printf("sys_exit\n");
    return -1;   
}

int sys_fork (regs *r){
    My_printf("sys_fork\n");
    return -1;   
}

int sys_read (regs *r){
    My_printf("sys_read\n");
    return -1;   
}

int sys_write (regs *r){
    My_printf("sys_write\n");
    return -1;   
}

int sys_open (regs *r){
    My_printf("sys_open\n");
    return -1;   
}

int sys_close (regs *r){
    My_printf("sys_close\n");
    return -1;   
}
