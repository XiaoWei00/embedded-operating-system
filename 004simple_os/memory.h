#ifndef _MEMORY_H_
#define _MEMORY_H_


#include "type.h"
#include "lib.h"

/*ҳ�Ĵ�С�ǹ̶������,4K*/

typedef struct page_s
{
	u32 vaddr; /*��ʼ��ַ*/
	u32 flags;
	s32 order;
	struct memcache_s *pmc;
	list_head list; /*ͨ��˫������*/
}page;

#define PAGE_SIZE (1 << 12) /*4KB*/
#define PAGE_MASK (~(PAGE_SIZE - 1))
#define PAGE_T_SIZE (sizeof(page))

#define CMEM_END 0X30700000
#define CMEM_START 0X30300000 

#define PAGE_T_START (PAGE_T_END - (PAGE_NUM * PAGE_T_SIZE)) //  0X306A090
#define PAGE_T_END CMEM_END //0X3070 0000 

#define PAGE_START ((CMEM_START + ~(PAGE_MASK)) & (PAGE_MASK))/*4KB����*/ //0X30300000 
#define PAGE_END ((CMEM_END - PAGE_START)/ (PAGE_SIZE + PAGE_T_SIZE) * PAGE_SIZE) + PAGE_START //4169728 0X3FA000 0X306FA000
#define PAGE_NUM ((PAGE_END - PAGE_START) / PAGE_SIZE)//1018

/*
buddy
*/
/*
flags
*/
#define PAGE_AVAILABLE 0X00
#define PAGE_DIRTY 0X01
#define PAGE_BUDDY_BUSY 0X02

#define MAX_BUDDY_ORDER 8
#define BUDDY_TYPE  (MAX_BUDDY_ORDER + 1)

#define PAGE_NUM_FOR_MAX_BUDDY ((1 << MAX_BUDDY_ORDER) - 1)

#define buddy_end(pg,order) ((pg) + ((1 << (order)) - 1))
#define next_buddy(pg,order) ((pg) + (1 << (order))) 
#define prev_buddy(pg,order) ((pg) - (1 << (order)))


void page_map_init(void);
void *get_free_pages(s32 order);
void put_free_pages(void * addr, s32 order);


/*
slab
*/
typedef struct memcache_s
{
	u32 memcacheNum; //�������ڴ����Ŀ
	u32 memcacheSize; //���ڴ���С
	u32 memcacheBuddyOrder;
	page *memcachePageStart;
	page *memcachePageEnd;
	void *nextcache;
}memcache;

/*
��page�����ʵĽǶ�������slab
*/
#define MEMCACHE_DEFAULT_ORDER (0)
#define MEMCACHE_MAX_ORDER (5)
#define MEMCACHE_MAX_PAGEWAST (PAGE_SIZE * 10 / 100 ) /*float*/
#define BUDDY_PAGES_NUM(order) ( 1 << (order))

/*
kmalloc
*/

#define SLAB_MAX_SIZE 1024
#define SLAB_BASE_SIZE 32
#define SLAB_NUM (SLAB_MAX_SIZE / SLAB_BASE_SIZE)

int kmalloc_init(void);
void *kmalloc(u32 size);
void kfree(void *addr);

#endif




