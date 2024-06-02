## Compiler
CC=$(HOME)/opt/cross/bin/i686-elf-gcc

OBJCP=$(HOME)/opt/cross/bin/i686-elf-objcopy
## Linker
LD=$(HOME)/opt/cross/bin/i686-elf-ld

## Directory to write binaries to
BIN=./HellEnter
## Compiler Flags
FLAGS=-g -ffreestanding -Wall -Wextra -fno-exceptions -m32 -std=c11


SRC=$(wildcard *.c)


LDPRIORITY := $(BIN)/Kernel/kernel_entry.o $(BIN)/Kernel/kernel.o $(BIN)/Libc/terminal.o  $(BIN)/CPU/GDT/gdt.o $(BIN)/CPU/IDT/isr.o $(BIN)/CPU/IDT/irq.o $(BIN)/CPU/IDT/idt.o $(BIN)/CPU/IDT/interrupt.o $(BIN)/CPU/GDT/gdt_loader.o $(BIN)/Drivers/keyboard.o

LL :=  $(shell find ./ -name "*.o" | xargs)




NASMENV=-I/home/user/OS/operating-system/Test/Memory/


my: clean

	mkdir -p ./$(BIN)/Libc
	mkdir -p $(BIN)/Kernel
	mkdir -p $(BIN)/Memory
	mkdir -p $(BIN)/Utils
	mkdir -p $(BIN)/CPU
	mkdir -p $(BIN)/CPU/Timer
	mkdir -p $(BIN)/CPU/IDT
	mkdir -p $(BIN)/CPU/GDT
	mkdir -p $(BIN)/FileSystem
	mkdir -p $(BIN)/SystemCalls
	mkdir -p $(BIN)/Drivers
	mkdir -p $(BIN)/Shell
	nasm -f bin $(NASMENV) Bootloader/boot.asm -o $(BIN)/boot.bin
	##nasm Bootloader/boot.asm -f bin -o $(BIN)/boot.bin
	nasm Kernel/empty_end.asm -f bin -o $(BIN)/empty_end.bin
	nasm Bootloader/kernel_entry.asm -f elf -o $(BIN)/Kernel/kernel_entry.o
	nasm Bootloader/gdt.asm -f elf -o $(BIN)/CPU/GDT/gdt.o
	nasm CPU/interrupt.asm -f elf -o $(BIN)/CPU/IDT/interrupt.o
	nasm CPU/gdt_loader.asm -f elf -o $(BIN)/CPU/GDT/gdt_loader.o

	##files
	$(CC) $(FLAGS) -c ./Kernel/kernel.c -o $(BIN)/Kernel/kernel.o
	$(CC) $(FLAGS) -c ./Libc/terminal.c -o $(BIN)/Libc/terminal.o 
	$(CC) $(FLAGS) -c ./Libc/string.c -o $(BIN)/Libc/string.o 
	$(CC) $(FLAGS) -c ./Libc/memory.c -o $(BIN)/Libc/memory.o
	$(CC) $(FLAGS) -c ./Libc/stdio.c -o $(BIN)/Libc/stdio.o
	$(CC) $(FLAGS) -c ./Libc/PMM.c -o $(BIN)/Libc/PMM.o
	$(CC) $(FLAGS) -c ./Memory/paging.c -o $(BIN)/Memory/paging.o
	$(CC) $(FLAGS) -c ./Memory/VMM_Help.c -o $(BIN)/Memory/VMM_Help.o
	$(CC) $(FLAGS) -c ./Memory/VMM.c -o $(BIN)/Memory/VMM.o
	$(CC) $(FLAGS) -c ./Libc/bitmap.c -o $(BIN)/Libc/bitmap.o
	$(CC) $(FLAGS) -c ./Memory/heap.c -o $(BIN)/Memory/heap.o
	$(CC) $(FLAGS) -c ./Utils/port_io.c -o $(BIN)/Utils/port_io.o
	$(CC) $(FLAGS) -c ./Utils/assert.c -o $(BIN)/Utils/assert.o
	$(CC) $(FLAGS) -c ./Utils/Conversions.c -o $(BIN)/Utils/Conversions.o
	$(CC) $(FLAGS) -c ./Libc/disk.c -o $(BIN)/Libc/disk.o
	$(CC) $(FLAGS) -c ./CPU/timer.c -o $(BIN)/CPU/Timer/timer.o
	$(CC) $(FLAGS) -c ./FileSystem/fs.c -o $(BIN)/FileSystem/fs.o
	$(CC) $(FLAGS) -c ./FileSystem/fs.c -o $(BIN)/FileSystem/fs.o
	$(CC) $(FLAGS) -c ./CPU/gdt.c -o $(BIN)/CPU/GDT/gdt.o
	$(CC) $(FLAGS) -c ./CPU/idt.c -o $(BIN)/CPU/IDT/idt.o
	$(CC) $(FLAGS) -c ./CPU/isr.c -o $(BIN)/CPU/IDT/isr.o
	$(CC) $(FLAGS) -c ./CPU/irq.c -o $(BIN)/CPU/IDT/irq.o
	$(CC) $(FLAGS) -c ./SystemCalls/syscalls.c -o $(BIN)/SystemCalls/syscalls.o
	$(CC) $(FLAGS) -c ./Drivers/keyboard.c -o $(BIN)/Drivers/keyboard.o
	$(CC) $(FLAGS) -c ./Shell/Shell.c -o $(BIN)/Shell/Shell.o
	$(CC) $(FLAGS) -c ./Shell/shellFunctions.c -o $(BIN)/Shell/shellFunctions.o
	$(CC) $(FLAGS) -c ./Shell/functions/text.c -o $(BIN)/Shell/text.o
	$(CC) $(FLAGS) -c ./Shell/functions/memory.c -o $(BIN)/Shell/memory.o
	$(CC) $(FLAGS) -c ./Shell/functions/misc.c -o $(BIN)/Shell/misc.o





	

	$(LD) -o $(BIN)/kernel.elf -Ttext 0x8200 $(LDPRIORITY) --start-group $(filter-out $(LDPRIORITY) ,  $(LL)) --end-group --oformat elf32-i386
	$(OBJCP) -O binary $(BIN)/kernel.elf $(BIN)/kernel.bin

	cat $(BIN)/boot.bin > $(BIN)/both_boot.bin
	cat $(BIN)/both_boot.bin $(BIN)/kernel.bin > $(BIN)/short.bin
	cat $(BIN)/short.bin $(BIN)/empty_end.bin > os_image.bin
	##dd if=/dev/zero of=osimage_formated.bin bs=512 count=2880 >/dev/null
	##dd if=os_image.bin of=osimage_formated.bin conv=notrunc >/dev/null

	qemu-system-x86_64 -drive format=raw,file=os_image.bin,index=0,if=floppy,  -m 256M


clean:
	rm -r $(BIN)




##to compile all of our c files. taken from someone, dont kill me!
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $(BIN)/$(subst .c,.o,$<) $(addprefix -I ,$(shell dirname $(shell echo $(CSRC) | tr ' ' '\n' | sort -u | xargs)))