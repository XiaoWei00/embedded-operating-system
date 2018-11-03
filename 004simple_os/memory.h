#ifndef _MEMORY_H_
#define _MEMORY_H_


#include "type.h"
#include "lib.h"

/*页的大小是固定不变的,4K*/
typedef struct page_s
{
	u32 vaddr; /*起始地址*/
	u32 flags;
	s32 order;
	list_head list; /*通用双向链表*/
}page;


#define PAGE_SIZE (1 << 12) /*4KB*/
#define PAGE_MASK (~(PAGE_SIZE - 1))
#define PAGE_T_SIZE (sizeof(page))

#define CMEM_END 0X30700000
#define CMEM_START 0X300F0000


#define PAGE_T_START (PAGE_T_END - (PAGE_NUM * PAGE_T_SIZE))
#define PAGE_T_END CMEM_END

#define PAGE_START ((CMEM_START + ~(PAGE_MASK)) & (PAGE_MASK))/*4KB对齐*/
#define PAGE_END ((CMEM_END - PAGE_START)/ (PAGE_SIZE + PAGE_T_SIZE) * PAGE_SIZE) + PAGE_START
#define PAGE_NUM ((PAGE_END - PAGE_START) / PAGE_SIZE)

/*
BUDDY
*/
/*
flags
*/
#define PAGE_AVAILABLE 0X00
#define PAGE_DIRTY 0X01
#define PAGE_BUDDY_BUSY 0X02

#define MAX_BUDDY_PAGE_NUM (9)

#define PAGE_NUM_FOR_MAX_BUDDY ((1 << MAX_BUDDY_PAGE_NUM) - 1)

#define buddy_end(x,order) ((x) + ((1 << (order)) - 1))
#define next_buddy(x,order) ((x) + (1 << (order))) 
#define prev_buddy(x,order) ((x) - (1 << (order)))


void page_map_init(void);
void *get_free_pages(s32 order);
void put_free_pages(void * addr, s32 order);
#endif




