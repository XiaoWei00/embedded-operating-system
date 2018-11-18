
#include "elf.h"
#include "lib.h"



u32 elf_get_exeaddr(char * elfFile)
{
	if(elfFile == NULL)
		return FALSE;

	elffilehead *efhead = (elffilehead *)elfFile;

	u32 exeaddr = efhead->elfEntry;

	elfprogramhead *ephead = (elfprogramhead *)(efhead->elfPhoff + (u32)efhead);

	u32 i = 0;
	for(i = 0; i < efhead->elfPhnum; i++)
	{
		memcpy((char *)(ephead->pOffset + (u32)efhead),(char *)ephead->pPaddr,ephead->pFsize);
		ephead++;
	}	
	
	return exeaddr;
}

