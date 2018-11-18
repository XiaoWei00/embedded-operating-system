

#ifndef _ELF_H_ 
#define _ELF_H_

#include "type.h"
/*
ELF file header

Programs header : description segment

segments: code

sections: optional
*/


#define elf32_word u32
#define elf32_hword  u16
#define elf32_addr  u32
#define elf32_sword  s32
#define elf32_offset u32

//elfType
#define ELF_TYPE_EXEC 0X02

//elfMachine
#define ELF_MACHINE_ARM 0X28


//elfVersion
#define ELF_VERSION 1
typedef struct elffilehead_t
{
	elf32_word elfInfo[4];
	elf32_hword elfType;
	elf32_hword elfMachine;
	elf32_word elfVersion;
	elf32_addr elfEntry; // entry address
	elf32_offset elfPhoff; // the start of the program header table
	elf32_offset elfShoff; // the start of the section header table
	elf32_word elfFlags;
	
	elf32_hword elfEhsize; // the size of this header
	elf32_hword elfPhsize; // the size of a program header 
	elf32_hword elfPhnum; // the number of entries in the program header table 
	elf32_hword elfShsize; // the size of a section header
	elf32_hword elfShnum; // the number of entries in the section header table
	elf32_hword elfShindex;		
}elffilehead;

//pType
#define P_TYPE_LOAD 0X1

typedef struct elfprogramhead_t
{
	elf32_word pType;
//	elf32_word pFlags; //64-bit
	elf32_word pOffset; // offset of the segment in the file image
	elf32_word pVaddr;  // Virtual address of the segment in memory
	elf32_word pPaddr; // physical address
	elf32_word pFsize; //  size in bytes of the segment in the fie image 
	elf32_word pMsize; //  size  in bytes of the segment in the memory
	elf32_word pFlags; //32-bit
	elf32_word pAlign; // 0 and  1 specify no alignment. integral power of 2

}elfprogramhead;

u32 elf_get_exeaddr(char *elfFile);

#endif



