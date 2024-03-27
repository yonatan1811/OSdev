#include "fs.h"
#include "../include/stdio.h"
#include "../Utils/bitmap.h"
#include "../Memory/heap.h"
#include "../Drivers/disk.h"

//First thing we have to do is a way to convert the files into a byte array. we cant just write a file object into our memory...

//lets make it:


#define SECTORS_PER_DIRECTORY 1


//this function is very simple to understand.
//we get a file and an initilized byte array.
//we simply transfer the data the file contains into bytes.
void write_file_to_byte_array(const FILE* file, unsigned char* byte_array) {
    // Copy file_name string to byte array
    strcpy((char*)byte_array, file->file_name);
    byte_array += strlen(file->file_name) + 1;  // Move the byte pointer to next position
    
    // Copy type, permissions, first_sector as char values to byte array
    *(byte_array++) = file->type;
    *(byte_array++) = file->permissions;
    *(byte_array++) = (char)(file->first_sector);
    
    // Split num_sectors into four bytes and copy to byte array
    *(byte_array++) = (char)(file->num_sectors >> 24);
    *(byte_array++) = (char)(file->num_sectors >> 16);
    *(byte_array++) = (char)(file->num_sectors >> 8);
    *(byte_array++) = (char)(file->num_sectors);
}


//this function will write number of files into our memory
unsigned char* write_files_to_byte_array(FILE** file_list, int file_num, int * total_size_return){
    
    // Calculate the total size required for the byte array (4 = header size)
    int total_size = 4;
    for (int i = 0; i < file_num; i++) {
//         kprint("file name length: ");
//         kprint(toString(strlen(file_list[i]->file_name), 10));
//         kprint("\n");
        total_size += strlen(file_list[i]->file_name) + 1;  // Include the null terminator
        total_size += sizeof(char) * 3;  // type, permissions, first_sector
        total_size += sizeof(int);  // num_sectors
	}



	unsigned char* byte_array = (unsigned char*)kmalloc(total_size);
    
    if (byte_array == NULL) return NULL;
    
    // Split file_num into four bytes and copy to byte array
    *(byte_array++) = (char)(file_num >> 24);
    *(byte_array++) = (char)(file_num >> 16);
    *(byte_array++) = (char)(file_num >> 8);
    *(byte_array++) = (char)(file_num);
    
    // Write the struct values to the byte array
    unsigned char* current_byte = byte_array;
    for (int i = 0; i < file_num; i++) {
        write_file_to_byte_array(file_list[i], current_byte);
        current_byte += strlen(file_list[i]->file_name) + 1 + sizeof(char) * 3 + sizeof(int);
    }
    *total_size_return = total_size;
    
    return byte_array - 4; // Subtract header length
}



FILE** get_files_from_byte_array(const unsigned char* byte_array, int* file_num_return) {
    
    int file_num = 0;
    file_num |= *(byte_array++) << 24;
    file_num |= *(byte_array++) << 16;
    file_num |= *(byte_array++) << 8;
    file_num |= *(byte_array++);
    
    *file_num_return = file_num;
    
    // Allocate memory for the struct pointers
    FILE** file_list = (FILE**)kmalloc(file_num * sizeof(FILE*));
    
    if (file_list == NULL) return NULL;
    
    // Iterate over the byte array to reconstruct struct instances
    const unsigned char* current_byte = byte_array;
    for (size_t i = 0; i < file_num; i++) {
        // Allocate memory for the struct instance
        file_list[i] = (FILE*)kmalloc(sizeof(FILE));
        
        if (file_list[i] == NULL) return NULL;
        
        // Copy file_name string from byte array
        size_t file_name_length = strlen((const char*)current_byte) + 1;
        file_list[i]->file_name = (char*)kmalloc(file_name_length);
        if (file_list[i]->file_name == NULL) return NULL;
            
        strcpy(file_list[i]->file_name, (const char*)current_byte);
        
        current_byte += file_name_length;  // Move the byte pointer to next position
        
        // Copy type, permissions, first_sector as char values from byte array
        file_list[i]->type = *(current_byte++);
        file_list[i]->permissions = *(current_byte++);
        file_list[i]->first_sector = (int)(*current_byte++);
        
        // Reconstruct num_sectors from four bytes in the byte array
        file_list[i]->num_sectors = 0;
        file_list[i]->num_sectors |= (int)(*current_byte++) << 24;
        file_list[i]->num_sectors |= (int)(*current_byte++) << 16;
        file_list[i]->num_sectors |= (int)(*current_byte++) << 8;
        file_list[i]->num_sectors |= (int)(*current_byte++);
    }
    
    return file_list;
}



FILE** get_root_dir(int disk , int** file_num)
{
	//just reading the memory of the disk from the start so we can get all the files and then sending them all to get files from byte array

	uint16_t* addr = kmalloc(SECTORS_PER_DIRECTORY * 256 * sizeof(uint16_t));

	if (!addr)
		return NULL; // if the addr is invalid we are going to do nothing.


	unsigned char * addr_8 = kmalloc(SECTORS_PER_DIRECTORY * 256); //because we could only write to the last 8 bytes of memory.

	if(!addr_8) return NULL; // if this address is invalid we are going to do nothing also

	LBA28_read_sector(disk, 1, SECTORS_PER_DIRECTORY, addr); // reading number of sectors starting from the address we gave

	for (int i = 0 ; i < 256; i++)
        addr_8[i] = addr[i] & 0xFF, 0;              // & 0xff ~ only read lowest 8 bits
    
    int * file_num_return = 0;
    //getting the files by the function we made before . FILE** -> a directory.
    FILE** result = get_files_from_byte_array(addr_8, file_num_return);

    if (!result) return NULL;

    file_num = &file_num_return;
    
    return result;
}

void list_files(FILE** folder , int number)
{
	for (int i = 0; i < number; ++i)
	{
		My_puts("File's name: ");
		My_printf("%s" , folder[i]->file_name);
		My_puts("\nFile's type: ");
		My_printf("%c" , folder[i]->type);
		My_puts("\nFile's permissions : ");
		My_printf("%c" , folder[i]->permissions);
	}
}



//wow, we are creating a new fileeee!!! well you might laugh rn, we are going to get all the files that are written right now, append a new file, and write every thing right back.
int new_file (int disk, char* name, char type, char permissions, int first_sector, int num_sectors, bitmap_t disk_bitmap, int bitmap_size)
{
	int* file_num = 0;
	//creating a new file. so exciting
	FILE* new = kmalloc(sizeof(FILE));

	if(!new){return -1;}

	new -> file_name = name;
    new -> type = type;
    new -> permissions = permissions;
    new -> first_sector = first_sector;
    new -> num_sectors = num_sectors;


    //getting all the files from the disk
    FILE ** old_files = get_root_dir (disk, &file_num);


    if(!old_files)
    	return -1;

    FILE ** new_files = kmalloc(sizeof(FILE *) * (*file_num + 1));
    
    if (!new_files) return -1;
    
    for (int i = 0; i < *file_num ; i++) new_files[i] = old_files[i];
    
    kfree(old_files, sizeof(FILE *) * (*file_num));
    
    My_printf("%d" , *file_num);
    
    new_files [*file_num] = new;
    
     
    int total_size;
    unsigned char * new_file_array = write_files_to_byte_array (new_files, *file_num + 1, &total_size);
    
    if(!new_file_array) return -1;
    
    uint16_t * array_16 = kmalloc(total_size * sizeof(uint16_t));
    
    if (!array_16) return -1;
    
    for (int i = 0 ; i < total_size; i++)
        array_16[i] = (uint16_t)new_file_array[i];
    
    LBA28_write_sector(disk, 1, SECTORS_PER_DIRECTORY, array_16);
    
    if(first_sector + num_sectors > bitmap_size) return -1;
    
    for(int i = first_sector; i < first_sector + num_sectors; i++)
        set_bitmap(disk_bitmap, i);

    return 0; //success
}




int initial_file (int disk, char* name, char type, char permissions, int first_sector, int num_sectors, bitmap_t disk_bitmap, int bitmap_size)
{
	int *file_num = 0;
    
    FILE * new = kmalloc(sizeof(FILE));
    if (!new) return -1;
    new -> file_name = name;
    new -> type = type;
    new -> permissions = permissions;
    new -> first_sector = first_sector;
    new -> num_sectors = num_sectors;
    
    FILE ** new_files = kmalloc(sizeof(FILE *));
    if (!new_files) return -1;
    
    new_files [0] = new;
    int total_size;
    
    unsigned char * new_file_array = write_files_to_byte_array (new_files, 1, &total_size);
    if(!new_file_array) return -1;
    
//     kprint(toString(total_size, 10));

    uint16_t * array_16 = kmalloc(total_size * sizeof(uint16_t));
    if (!array_16) return -1;
    
    for (int i = 0 ; i < total_size; i++)
        array_16[i] = (uint16_t)new_file_array[i];
    
    LBA28_write_sector(disk, 1, SECTORS_PER_DIRECTORY, array_16);
    
    if(first_sector + num_sectors > bitmap_size) return -1;
    
    for(int i = first_sector; i < first_sector + num_sectors; i++)
        set_bitmap(disk_bitmap, i);

    return 0; //success
}

int get_free_sector(int size, bitmap_t disk_bitmap, int bitmap_size)
{
	int consecutive = 0;
    int result = 1 + SECTORS_PER_DIRECTORY;     // sectors start from 1, + root directory space.
    for (int i = 1 + SECTORS_PER_DIRECTORY; i < bitmap_size; i++){
        if (get_bitmap(disk_bitmap, i) == 0)
            consecutive ++;
        else{
            consecutive = 0;
            result = i+1;
        }
        if (consecutive >= size) return result;
    }
    return -1;
}

int new_file_alloc(int disk, char* name, char type, char permissions, int num_sectors, bitmap_t disk_bitmap, int bitmap_size)
{
	int position = get_free_sector(num_sectors, disk_bitmap, bitmap_size);
    if(position < 0) return -1;
    new_file (disk, name, type, permissions, position, num_sectors, disk_bitmap, bitmap_size);
    return 0;
}

int initial_file_alloc(int disk, char* name, char type, char permissions, int num_sectors, bitmap_t disk_bitmap, int bitmap_size)
{
	int position = get_free_sector(num_sectors, disk_bitmap, bitmap_size);
    if(position < 0) return -1;
    initial_file(disk, name, type, permissions, position, num_sectors, disk_bitmap, bitmap_size);
    return 0;
}







//write to meee
int write_file (int disk, FILE* file, uint16_t* contents, int content_size){
    if (content_size != file -> num_sectors) return -1;      // size measured in sectors
    
    LBA28_write_sector(disk, file -> first_sector, content_size, contents);
    return 0;
}

int read_file (int disk, FILE* file, uint16_t* contents, int content_size){
    if (content_size != file -> num_sectors) return -1;      // size measured in sectors
    
    LBA28_read_sector(disk, file -> first_sector, content_size, contents);
    
    //TODO check if read went ok
    
    return 0;
}



