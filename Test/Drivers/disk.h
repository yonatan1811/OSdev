#ifndef DISK_H
#define DISK_H

#include "../Utils/Typedefs.h"
#include "../Utils/port_io.h"
#include "../include/stdio.h"




// ** taken from here , https://wiki.osdev.org/ATA_PIO_Mode

//some typedefs for our disk
typedef struct{
    char drivetype;
    short sectors;
    short cylinders;
    char heads;
    char drives;
}
disk_info;


typedef struct{
    char bl;
    char ch;
    char cl;
    char dh;
    char dl;
}
raw_disk_info;



/*
* this function will detect and initialize a disk.
* 
*/
void identify_ata(uint8_t drive);


/*
* with these two uniuqe functions we will be able to read and write to sectors and we will be using these in the file system
*/
uint16_t* LBA28_read_sector(uint8_t drive, uint32_t LBA, uint32_t sector, uint16_t *addr);

void LBA28_write_sector(uint8_t drive, uint32_t LBA, uint32_t sector, uint16_t *buffer);

void decode_raw_disk_info(raw_disk_info dinfo, disk_info * result);


raw_disk_info retrieve_disk_info();


#endif