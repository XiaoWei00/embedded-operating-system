
#include "fs.h"
#include "romfs.h"
#include "lib.h"
#include "memory.h"

fs *fileSys[MAX_FS_NUM];

static int fs_register(u32 num, fs *FS)
{
	if(num >= MAX_FS_NUM || FS == NULL)
		return -1;

	if(fileSys[num] != NULL)
		return -1;
	
	fileSys[num] = FS;

	return num;
}

static void fs_unregister(u32 num)
{
	fileSys[num] = NULL;
}


int fs_init(void)
{
	int ret = fs_register(ROMFS,&romfs);
	if(ret != -1)
    {
		fileSys[ROMFS]->fs_storage_format("romfs");
	}
	return ret;
}

char *get_filename(const char *name,char *filename)
{
	if(name ==	NULL || filename == NULL)
		return NULL;

	u8 i = 0, j = 0;
	
	while(name[j] != '\0')
	{
		if(name[j] == '/')
		{		
			i = 0;
			j++;
		}

		filename[i++] = name[j++];  
			
	}
	filename[i] = '\0';
	
	return filename;
}

/*

parameter:  name----      parentdir---- 

return: ÓàÏÂµÄ

*/
char *get_pdir_rname(const char *name, char *parentdir)
{
	if(name == NULL || parentdir == NULL)
		return NULL;

	while(*name != '\0')
	{
		if(*name == '/')
		{
			return (++name);
		}
		else
		{
			*parentdir++ = *name++;
		}	
	}	
	*parentdir = '\0';
	return NULL;
}	




