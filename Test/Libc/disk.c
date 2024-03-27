#include "../Drivers/disk.h"
#include "../include/stdio.h"
#include "../CPU/timer.h"


/*
just for me : 

port_io : 

outb(uint16_t port, uint8_t data);
void inb(uint16_t port , uint8_t data);

*/


//some defines
#define STATUS_RDY      0x40
#define STATUS_BSY      0x80


//The tutorial is right over here : https://wiki.osdev.org/ATA_PIO_Mode#IDENTIFY_command
void identify_ata(uint8_t drive)
{
	//To use the IDENTIFY command, select a target drive by sending 0xA0 for the master drive, or 0xB0 for the slave, to the "drive select" IO port. 
	//so 0xA0 is for master and 0xB0 is for slave
	
	//On the Primary bus, this would be port 0x1F6. 
	outb(0x1F6 , drive);
	outb(0x1F2, 0);
	outb(0x1F3, 0);
	outb(0x1F4, 0);
	outb(0x1F5, 0);
	outb(0x1F7, 0xEC);
	uint8_t tmp = inb(0x1F7);

	sleep(2);
	if(tmp & STATUS_RDY){
		switch(drive){
			case 0xA0:
				My_printf("Master Drive is the current active Drive \n");
				break;
			case 0xB0:
				My_printf("Slave Drive is the current active Drive \n");
				break;
		}
	}
	else
	{
		switch(drive){
			case 0xA0:
				My_printf("Master Drive is NOT the current active Drive \n");
				break;
			case 0xB0:
				My_printf("Slave Drive is NOT the current active Drive \n");
				break;
			}
	}
}


void wait_BSY(){
	while(inb(0x1F7) & STATUS_BSY);
}

void wait_DRQ(){
	while(!(inb(0x1F7) & STATUS_RDY));
}

//now for the real part. This function will read 
/*
;ATA PI0 28bit singletasking disk read function (up to 256 sectors)
; inputs: ESI -> driverdata info, EDI -> destination buffer
; BL = sectors to read, DX = base bus I/O port (0x1F0, 0x170, ...), EBP = 28bit "relative" LBA
; BSY and DRQ ATA status bits must already be known to be clear on both slave and master
; outputs: data stored in EDI; EDI and EBP advanced, EBX decremented
; flags: on success Zero flag set, Carry clear
*/
uint16_t* LBA28_read_sector(uint8_t drive, uint32_t LBA, uint32_t sector, uint16_t *addr)
{
	//convert relative LBA to absolute LBA
	LBA = LBA & 0x0FFFFFFF;

	wait_BSY();
    outb(0x1F6, drive | ((LBA >> 24) & 0xF));
	outb(0x1F1, 0x00);
    outb(0x1F2, sector);
    outb(0x1F3, (uint8_t) LBA);
    outb(0x1F4, (uint8_t)(LBA >> 8));
	outb(0x1F5, (uint8_t)(LBA >> 16)); 
	outb(0x1F7, 0x20); // 0x20 = 'Read' Command


	uint16_t *tmp = addr;

	for (int j = 0; j < sector; j ++){
		wait_BSY();
		wait_DRQ();
		for(int i = 0; i < 256; i++){
            tmp[i] = inw(0x1F0);
        }

		tmp += 256;
	}
	return addr;

}

//The 28 bit write mode is pretty much the same, instead of inw we are going to do outl, warning, we are only writing the lowest 8 bits

void LBA28_write_sector(uint8_t drive, uint32_t LBA, uint32_t sector, uint16_t *buffer)
{
	LBA = LBA & 0x0FFFFFFF;
	
	wait_BSY();
	outb(0x1F6, drive | ((LBA >> 24) & 0xF));		// send drive and bits 24 - 27 of LBA
	outb(0x1F1, 0x00);								// ?
	outb(0x1F2, sector);							// send number of sectors
	outb(0x1F3, (uint8_t) LBA);						// send bits 0-7 of LBA
	outb(0x1F4, (uint8_t) (LBA >> 8));				// 8-15
	outb(0x1F5, (uint8_t) (LBA >> 16)); 			// 16-23
	outb(0x1F7,0x30); 								// 0x30 = 'Write' Command

	uint32_t *tmp = buffer;
	
	for (int j = 0; j < sector; j++){
		wait_BSY();
		wait_DRQ();

		for(int i = 0; i < 256; i++){
			outl(0x1F0, tmp[i]);
		}

		outb(0x1F7, 0xE7);
		sleep(1);
		
		tmp += 256;
	}
}
