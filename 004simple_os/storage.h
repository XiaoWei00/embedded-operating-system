
#ifndef _STORAGE_H_
#define _STORAGE_H_


#include "type.h"

/*
ͨ�õĴ洢�豸:

�洢�豸�ľ���λ��� �洢�豸�ķ���

�洢�豸����С�洢��

�洢�豸��������

*/
typedef struct storage_t storage;

struct storage_t
{
	u32 start_pos;
	u32 sector_size;
	u32 storage_size;

	void *(* dout)(storage *sd, u32 addr, void *des, u32 size);
	void *(* din)(storage *sd, u32 addr ,const void *src, u32 size);	
};


#define RAMDISK 0
#define MAX_STORAGE_NUM 2



#define RAMDISK_CAPACITY 0X100000
#define RAMDISK_SECTOR_NUM 2
#define RAMDISK_SECTOR_SIZE (RAMDISK_CAPACITY / RAMDISK_SECTOR_NUM)

#define RAMDISK_SATRT 0X30700000

extern storage ramdisk;
extern storage *storage_device[MAX_STORAGE_NUM];

int ramdisk_init(void);



#endif 


