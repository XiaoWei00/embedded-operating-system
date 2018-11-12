
#include "fs.h"
#include "storage.h"
#include "lib.h"
#include "memory.h"
#include "romfs.h"

static void romfs_write_file(const char * buff, u32 buffSize, const char * name);
static char *romfs_read_file(char * buff, const char * name);
static void romfs_storage_format(const char * name);

fs romfs = 
{
	/*
	.filename2inode = romfs_filename2inode,
	.inode2fileaddr = romfs_inode2fileaddr,
	*/
	.fs_write_file = romfs_write_file,
	.fs_read_file = romfs_read_file,
	.fs_storage_format = romfs_storage_format,
	
	.fsStorage = &ramdisk,
	.fsName = "romfs",
};

/*
static addr_t romfs_get_filedateaddr(addr_t fileaddr,size_t filenameSize)
{
	return (fileaddr + FILEHEAD_SIZE + ADDR_ALIGN(filenameSize,ROMFS_FILE_ALIGN_BYTES)); 
}

static inode *romfs_filename2inode(char *filename,fs *FS)
{
	if(filename == NULL || FS == NULL)
		return NULL;
	
	//判断被操作的文件系统是否为所能支持的
//	FS->fsStorage->dout()

	
}
static addr_t romfs_inode2fileaddr(inode *node)
{
	 size_t nameLength = strlen(node->fileName);
	 return romfs_get_filedateaddr(node->fileAddr,nameLength);
}
*/

/*设备格式化*/
static void romfs_storage_format(const char *name)
{
	if(name == NULL)
		return; 

	u32 nameLen = strlen(name) + 1;
	u32 fsSize = sizeof(romfshead) + ADDR_ALIGN(nameLen,16);/*32*/

	romfshead fshead =
	{
		.romfsFlag1 = ROMFS_HEAD_FLAG1,
		.romfsFlag2 = ROMFS_HEAD_FLAG2,
		.romfsSize =  s2b_32_endian(fsSize),
		.romfsChecksum = 0x12345678, /*don't checksum*/
	};	
	
	romfs.fsStorage->din(romfs.fsStorage,0,&fshead,sizeof(fshead));
	romfs.fsStorage->din(romfs.fsStorage,sizeof(fshead),name,nameLen);
}

static size_t romfs_get_size(void)
{
	u32 size = 0;
	romfs.fsStorage->dout(romfs.fsStorage,8,&size,sizeof(size));
	return b2s_32_endian(size);
}	

static bool romfs_empty(void)
{
	
	if(romfs_get_size() <= 32)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}	


static void romfs_amend_prefile_head(u32 pfileStartAddr,u32 waddr)
{
		
	u32 nextM;	
	romfs.fsStorage->dout(romfs.fsStorage,pfileStartAddr,&nextM,sizeof(nextM));

	u32 bwaddr = s2b_32_endian(waddr);
		
	/*上一个是目录*/
	if((b2s_32_endian(nextM) == (DIR | EXE)) )
	{	
		/*修改附加信息*/
		romfs.fsStorage->din(romfs.fsStorage,(pfileStartAddr + 4),&bwaddr,sizeof(bwaddr));
	}
	
	waddr = s2b_32_endian(waddr | b2s_32_endian(nextM));
		
	romfs.fsStorage->din(romfs.fsStorage,pfileStartAddr,&waddr,sizeof(waddr));
	
}


static u32 romfs_write_curfile_head(char *name,romfsfilehead *head,u32 waddr)
{
	u32 dirlen = strlen(name) + 1;
	size_t adirlen = ADDR_ALIGN(dirlen, 16);

	romfs.fsStorage->din(romfs.fsStorage,waddr,head,sizeof(*head));
	romfs.fsStorage->din(romfs.fsStorage,(waddr + 16),name,dirlen);

	u32 endAddr = waddr + 16 + adirlen;

	return endAddr;
}	

static u32 romfs_processdir(char *dir,u32 pfileStartAddr)
{
	u32 waddr = ADDR_ALIGN(romfs_get_size(),16);

	if(pfileStartAddr != 0)
		romfs_amend_prefile_head(pfileStartAddr,waddr);
	
	romfsfilehead dirhead =
		{
			.nextM = s2b_32_endian(DIR | EXE),
			.spec = 0,
			.fileSize = 0,
			.fileChecksum = 0x12345678,
		};
	
	u32 endAddr = s2b_32_endian(romfs_write_curfile_head(dir, &dirhead,waddr));
	
	/*amend file system size*/
	romfs.fsStorage->din(romfs.fsStorage,8,&endAddr,sizeof(endAddr));

	return waddr;
		
}	


static void romfs_processfile(char *name,char *buff,u32 buffSize,u32 pfileStartAddr)
{
	u32 waddr = ADDR_ALIGN(romfs_get_size(),16);

	if(pfileStartAddr != 0)
		romfs_amend_prefile_head(pfileStartAddr,waddr);

	romfsfilehead filehead =
	{
		.nextM = s2b_32_endian(RE_FILE | EXE),
		.spec = 0,
		.fileSize = s2b_32_endian(buffSize),
		.fileChecksum = 0x12345678,
	};

	/*write file head*/
	u32 endAddr = romfs_write_curfile_head(name,&filehead,waddr);
	
	/*write  file data*/
	romfs.fsStorage->din(romfs.fsStorage,endAddr,buff,buffSize);

	/*amend file system size*/	
	endAddr +=  buffSize;
	endAddr = s2b_32_endian(endAddr);
	romfs.fsStorage->din(romfs.fsStorage,8,&endAddr,sizeof(endAddr));	

}	
/*
name:包含完整路径的文件名
*/
static void romfs_write_file(const char *buff,u32 buffSize ,const char *name)
{
	if(buff == NULL || name == NULL || buffSize == 0)
		return;

	/*得到文件名，去除路径*/
	char filename[12] = {0};
	get_filename(name,filename); /**/

	char parentdir[6] = {0}; 
	char *rname = get_pdir_rname(name,parentdir);


	u32 pfileStartAddr = 0;

	if(romfs_empty())
	{
		info("romfs is empty");
		
		while(1)
		{	
			/*file system don't have any files*/
			
			/*剥离的是否为最终文件*/

			if(strcmp(filename,parentdir) == 0)
			{	

				romfs_processfile(filename,buff,buffSize,pfileStartAddr);
				break;
			}
			else
			{

				pfileStartAddr = romfs_processdir(parentdir,pfileStartAddr);
				rname = get_pdir_rname(rname,parentdir);
			}

		}	
		
	}
	else
	{
		info("romfs is not empty");
	}	

/*
	char testbuff[32] = {0};
	u32 i = 0;
	romfs.fsStorage->dout(romfs.fsStorage,0,testbuff,sizeof(testbuff));

	{	
		for(i = 0; i < 8; i++)
		{
			printfk("%c\r\n",testbuff[i]);//romfs 标志
		}
	
		for(i = 8; i < 16 ;i += 4)
		{	
			u32 tmp = *((u32 *)(testbuff  + i)); 
			printfk("tmp=%d\r\n",b2s_32_endian(tmp));
			printfk("tmp=%x\r\n",b2s_32_endian(tmp));
		}
	}
		printfk("fname=%s\r\n",testbuff + 16);


	
	romfs.fsStorage->dout(romfs.fsStorage,32,testbuff,sizeof(testbuff));

	{	

		for(i = 0; i < 16 ;i += 4)
		{	
			u32 tmp = *((u32 *)(testbuff  + i)); 
			printfk("tmp=%d\r\n",b2s_32_endian(tmp));
			printfk("tmp=%x\r\n",b2s_32_endian(tmp));
		}
	}
		printfk("fname=%s\r\n",testbuff + 16);

	romfs.fsStorage->dout(romfs.fsStorage,64,testbuff,sizeof(testbuff));

	{	

		for(i = 0; i < 16 ;i += 4)
		{	
			u32 tmp = *((u32 *)(testbuff  + i));
			printfk("tmp=%d\r\n",b2s_32_endian(tmp));
			printfk("tmp=%x\r\n",b2s_32_endian(tmp));
		}
	}
		printfk("fname=%s\r\n",testbuff + 16);	

	romfs.fsStorage->dout(romfs.fsStorage,94,testbuff,11);
	
	printfk("number=%s\r\n",testbuff);
*/
}	




static char *romfs_read_file(char *buff,const char *name)
{
	if(buff == NULL || name == NULL)
		return NULL;

	if(romfs_empty())
		return NULL;
	
	info("read fs is not empty");

	char filename[12] = {0};
	get_filename(name,filename); /**/

	char parentdir[6] = {0}; 
	char *rname = get_pdir_rname(name,parentdir);
			
	size_t fileSize = 0;
	u32 fileAddr = 0;
	
	//kmalloc
	romfsfilehead *pfilehead = (romfsfilehead *)kmalloc(sizeof(romfsfilehead) + MAX_FILE_NAMELEN);
	if(pfilehead == NULL)
		return NULL;

	info("kmalloc is success");
	
	romfs_get_first_filehead(pfilehead); 
	u32 next = 32;

	bool find = FALSE;

	while(1)
	{	
		/*目录*/

		if(strcmp(pfilehead->name,parentdir) == 0)
		{
			/*找到目录*/
			info("find dir");
			
			if(strcmp(parentdir,filename) == 0)
			{
				info("find file");
				//最后一个目录，即目标文件
				fileSize = pfilehead->fileSize;
				find = TRUE;
				break;
			}	
			else
			{
				u32 tmpnext	= b2s_32_endian(pfilehead->spec);
				if(tmpnext == 0)
					break;
				next = tmpnext;
			}	

			rname = get_pdir_rname(rname,parentdir);
		}
		else
		{
			/*没有找到目录*/
			u32 tmpnext = b2s_32_endian(pfilehead->nextM) & (~0xf);
			if(tmpnext == 0)
				break;
			next = tmpnext; 
		}	
		
		romfs_get_filehead(pfilehead,next);
	
		
	}	
		
	kfree(pfilehead);
	
	if(find == FALSE)
	{	
		info("don't find the file");
		return NULL;
	}

	fileSize = b2s_32_endian(fileSize);
	fileAddr = b2s_32_endian(fileAddr);
	
	fileAddr = next + 32;

	
	return romfs.fsStorage->dout(romfs.fsStorage,fileAddr,buff,fileSize);
	
}	


