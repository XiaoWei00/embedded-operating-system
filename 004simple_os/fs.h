
#ifndef _FS_H_ 
#define _FS_H_

#include "type.h"
#include "storage.h"

#define MAX_FS_NUM  2
#define ROMFS 0

typedef struct fs_t fs;

extern fs *fileSys[MAX_FS_NUM];
extern fs romfs;
/*
inode 索引节点
文件---inode 
*/
/*
file
file head
file data
*/

/*
typedef struct inode_t 
{
	char *fileName;
	size_t fileSize;
	addr_t fileAddr; //file head
	fs *fileFs;	
}inode;
*/

/*
file system 
*/
struct fs_t
{
	/*
	inode *(*filename2inode)(char *name,fs *FS); 
	addr_t (*inode2fileaddr)(inode *filenode);
	*/
	
	void (*fs_write_file)(const char * buff, u32 buffSize, const char * name);
	char *(*fs_read_file)(char * buff, const char * name);
	void (*fs_storage_format)(char * name);
	
	storage *fsStorage;	
	char *fsName;
};



int fs_init(void);

char *get_filename(const char * name, char * filename);
char *get_pdir_rname(const char * name, char * parentdir);
#endif




