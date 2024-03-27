#ifndef FS_H
#define FS_H

#include "../Utils/Typedefs.h"
#include "../Utils/bitmap.h"

//defines for our nodes

#define FS_FILE       0
#define FS_DIRECTORY  1
#define FS_INVALID    2


//lets say every file is acctully is a node. a node can simply be a file or a folder. 
//for now we will only have one folder. the root folder and "infinite" files. 
//*TODO - create a way to have folders. Folders is a file that points to a list of files.



//I know we can't use uppercase letters for types but it is easy for me to see it
typedef struct _FILE {
	char* file_name;
	char type;
	char permissions;
	int first_sector;
	int num_sectors;
	

}FILE;


//simple as dir : 
/*
* input - the folder we want to make dir on, number - number of files to show on the screen
* output - Just a print to the screen of the names of the files and their details.
*/
void list_files(FILE** folder , int number);


//creats a new file on our disk. very exciting.....
//isn't it? im feeling kind of dumb now.
int new_file (int disk, char* name, char type, char permissions, int first_sector, int num_sectors, bitmap_t disk_bitmap, int bitmap_size);


//will explain more about that in the future.
int initial_file (int disk, char* name, char type, char permissions, int first_sector, int num_sectors, bitmap_t disk_bitmap, int bitmap_size);


int get_free_sector(int size, bitmap_t disk_bitmap, int bitmap_size);

int new_file_alloc(int disk, char* name, char type, char permissions, int num_sectors, bitmap_t disk_bitmap, int bitmap_size);


int initial_file_alloc(int disk, char* name, char type, char permissions, int num_sectors, bitmap_t disk_bitmap, int bitmap_size);


//writing some contents to our file!! very exciting,....!!!
int write_file (int disk, FILE* file, uint16_t* contents, int content_size);



//reading the contents we have written before.... very exciting!!
int read_file (int disk, FILE* file, uint16_t* contents, int content_size);

#endif