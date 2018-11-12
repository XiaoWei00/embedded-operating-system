#include "storage.h"
#include "lib.h"


static void *ramdisk_dout(storage * sd, u32 addr, void * des, u32 size);
static void *ramdisk_din(storage * sd, u32 addr, void * src, u32 size);


storage *storage_device[MAX_STORAGE_NUM];

storage ramdisk = 
{
	.start_pos = RAMDISK_SATRT,
	.sector_size = RAMDISK_SECTOR_SIZE,
	.storage_size = RAMDISK_CAPACITY,

	.dout = ramdisk_dout,
	.din = ramdisk_din,
};

static void *ramdisk_dout(storage *sd, u32 addr, void *des, u32 size)
{	
	
	return memcpy((s8 *)(sd->start_pos + addr),des,size);
}	

static void *ramdisk_din(storage *sd, u32 addr, void *src, u32 size)
{
	return memcpy(src, (char *)(sd->start_pos + addr),size);
}	

static s32 storage_register(u32 num, storage *sd)
{
	if(num >= MAX_STORAGE_NUM || sd == NULL)
		return -1;

	if(storage_device[num] !=	NULL)
		return -1;

	storage_device[num] = sd;

	return num;
}

static s32 storage_unregister(u32 num)
{
		if(num >= MAX_STORAGE_NUM)
			return -1;

		storage_device[num] = NULL;

		return num;
}	
int ramdisk_init(void)
{
	return storage_register(RAMDISK,&ramdisk);	
}	






	

