

#ifndef _ROMFS_H_ 
#define	_ROMFS_H_

#include "fs.h"


#define FILESYS_NAMESIZE 8
#define FILEHEAD_SIZE 16
#define ROMFS_FILE_ALIGN_BYTES 16

#define ADDR_ALIGN(addr,bytes)    ( ((addr) + ((bytes) - 1) ) &   ~((bytes) - 1))


/*
romfs ´ó¶Ë¸ñÊ½
- :0X2D   r:0X72   o:0X6F   m:0x6D
1 :0X31   f:0x66   s:0x73   -:0x2d
*/
#define ROMFS_HEAD_FLAG1 	0X2D726F6D 
#define ROMFS_HEAD_FLAG2	0X3166732D

typedef struct romfshead_t
{
	u32 romfsFlag1;
	u32 romfsFlag2;
	u32 romfsSize;
	u32 romfsChecksum;
	char name[0];	
}romfshead;
/*char name[0] GNU C extend*/


#define HARD_LINK 0
#define DIR 1
#define RE_FILE 2

#define EXE 8


typedef struct romfsfilehead_t
{
	u32 nextM;
	u32 spec;
	u32 fileSize;
	u32 fileChecksum;
	char name[0];
}romfsfilehead;






/*'/0'*/
#define MAX_FILE_NAMELEN 16 



#define romfs_get_first_filehead(pfilehead) romfs.fsStorage->dout(romfs.fsStorage,32,(pfilehead),(sizeof(romfsfilehead) + MAX_FILE_NAMELEN))
#define romfs_get_filehead(pfilehead,addr) romfs.fsStorage->dout(romfs.fsStorage,addr,(pfilehead),(sizeof(romfsfilehead) + MAX_FILE_NAMELEN))



#endif



