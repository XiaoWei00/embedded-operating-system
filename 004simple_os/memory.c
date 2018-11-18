#include "memory.h"

#include "lib.h"

/*
buddy
*/

static list_head page_buddy[BUDDY_TYPE];

static void page_buddy_init(void)
{
	int i =0;
	for(i = 0; i < BUDDY_TYPE; i++)
	{
		listhead_init(&page_buddy[i]);
	}
}

void page_map_init(void)
{
	int i = 0;
	page *pg = (page *)PAGE_T_START;

	page_buddy_init();

	for(i = 0; i < PAGE_NUM; i++,pg++)
	{
		pg->flags = PAGE_AVAILABLE;
		pg->vaddr = PAGE_START + i * PAGE_SIZE;

		if(i < (PAGE_NUM & ~PAGE_NUM_FOR_MAX_BUDDY))
		{
			if((i & PAGE_NUM_FOR_MAX_BUDDY) == 0)
			{
				pg->order = MAX_BUDDY_ORDER;
			}
			else
			{
				pg->order = -1;
			}	
			list_add_tail(&page_buddy[MAX_BUDDY_ORDER],&(pg->list));
		}
		else
		{
			pg->order = 0;	
			list_add_tail(&page_buddy[0],&(pg->list));
		}	
	}	
}



static page *get_pages_from_list(s32 order)
{
	s32 tmporder = order;
	page *pg = NULL;
	for(; tmporder < BUDDY_TYPE; tmporder++)
	{	
		if(list_empty(&page_buddy[tmporder]))
		{
			continue;	
		}
		else
		{
			pg = list_entry(page_buddy[tmporder].next,page,list);
			list_head *ch = &(pg->list);
			list_head *ct = &(buddy_end(pg,tmporder)->list);

			list_remove_chain(ch,ct);
			
			for(tmporder--;tmporder >= order; tmporder--)
			{
				list_head *lh = &(pg->list);
				list_head *lt = &(buddy_end(pg,tmporder)->list);
				pg->order = tmporder;
				list_add_chain_tail(&page_buddy[tmporder],lh,lt);
				
				pg = next_buddy(pg, tmporder);
				
			}
			pg->order = order;
			pg->flags |= PAGE_BUDDY_BUSY;
			break;
		}	
	}

	return pg;
	
}	


static void put_pages_to_list(page *pg, s32 order)
{
	if((pg->flags & PAGE_BUDDY_BUSY) == 0)
	{
		return;
	}
	pg->flags &= ~PAGE_BUDDY_BUSY;

	bool nFlag = TRUE , pFlag = TRUE;
	page *npg = pg;
	page *ppg = pg;	
	for(; order < (BUDDY_TYPE - 1); order++)
	{	
		if(nFlag == TRUE)
			npg = next_buddy(pg, order);
		
		if((u32)npg >= PAGE_T_END)
		{
			npg = pg;
			nFlag = FALSE;
		}

		if(pFlag == TRUE)
			ppg = prev_buddy(pg, order);
		
		if((u32)ppg < PAGE_T_START)
		{
			ppg = pg;
			pFlag = FALSE;
		}
		
		if(nFlag == TRUE && ((npg->flags & PAGE_BUDDY_BUSY) == 0) && (npg->order == order))
		{
			list_head *nch = &(npg->list);
			list_head *nct = &(buddy_end(npg, order)->list);

			list_remove_chain(nch,nct);

			npg->order = -1;
			
			list_head *ct = &(buddy_end(pg, order)->list);

			ct->next = nch;
			nch->prev = ct;

			(pg->order)++;
			
			continue;
		}
		else if(pFlag == TRUE && ((ppg->flags & PAGE_BUDDY_BUSY) == 0) && (ppg->order == order))
		{
			list_head *pch = &(ppg->list);
			list_head *pct = &(buddy_end(ppg, order)->list);

			list_remove_chain(pch,pct);

			ppg->order = order + 1;

			pg->order = -1;

			list_head *ch = &(pg->list);

			pct->next = ch;
			ch->prev = pct;

			pg = ppg;
			
			continue;
		}
		else
		{
			break;
		}	
	
	}
	list_add_chain_head(&page_buddy[order],&(pg->list), &(buddy_end(pg, order)->list));
}

static page *alloc_pages(s32 order)
{
	page *pg = get_pages_from_list(order);

	if(pg == NULL)
		return NULL;

	int i = 0;
	for(; i < (1 << order); i++)
	{
		(pg + i)->flags |= PAGE_DIRTY;
	}	
	return pg;
}	

static void *page_addr(page *pg)
{
	return (void *)(pg->vaddr);
}	
void *get_free_pages(s32 order)
{
	if(order < 0 || order > 8)
		return NULL;
	
	page *pg = alloc_pages(order);
	if(pg == NULL)
		return NULL;
	return page_addr(pg);
}	
static page *addr_page(u32 addr)
{
	u32 offset = (addr - PAGE_START) / PAGE_SIZE;
	if(offset > PAGE_NUM)
		return NULL;
	return (page *)PAGE_T_START + offset;
}	
static void free_pages(page *pg,s32 order)
{
	int i = 0;
	for(; i < (1 << order); i++)
	{
		(pg + i)->flags &= ~PAGE_DIRTY;
	}	
	put_pages_to_list(pg,order);
}	
void put_free_pages(void *addr,s32 order)
{
	if(addr == NULL || order < 0 || order > 8)
		return ;
	free_pages(addr_page((u32)addr),order);
}	

/*
slab
*/
static s8 memcachesize_order(u32 size)
{
	s8 order = 0;
	for(; order <= MEMCACHE_MAX_ORDER; order++)
	{
		if(size <= MEMCACHE_MAX_PAGEWAST * BUDDY_PAGES_NUM(order))
		{
			return order;
		}	
	}	
	return -1;
}

static u32 manage_memcache(void *addr,s8 order,u32 size)
{
	u32 num = 1;
	s8 *p = (s8 *)addr;
	u32 *wp = (u32 *)addr;
		
	u32 aSize = PAGE_SIZE * BUDDY_PAGES_NUM(order) - size;
	for( ; size <= aSize; aSize -= size, num++)
	{
		p += size;
		*wp = (u32)p;
		wp = (u32 *)p;
	}
	*wp = NULL;
	
	return num;
}	


static memcache *creat_memcache(memcache *mc, u32 size)
{
	
	s8 order = memcachesize_order(size);

	if(order == -1)
		return NULL;
	
	page *pg = alloc_pages(order);
	if(pg == NULL)
		return NULL;
	
	mc->memcachePageStart = pg;
	int i = 0;
	for(i = 0; i < (1 << order); i++)
	{
		(pg + i)->pmc = mc;
	}		

	mc->memcachePageEnd = buddy_end(mc->memcachePageStart, order);
	mc->memcachePageEnd->list.next = NULL; // ? 
	mc->memcacheBuddyOrder = order;
	mc->memcacheSize = size;
	mc->nextcache = page_addr(mc->memcachePageStart);

	
	mc->memcacheNum = manage_memcache(mc->nextcache,order,size);

	return mc;
	
}

static void *alloc_obj_memcache(memcache *mc)
{
	if(mc == NULL)
		return NULL;
	
	u32 num = mc->memcacheNum;
	void *ret = NULL;
	if(num == 0)
	{
		page *pg = alloc_pages(mc->memcacheBuddyOrder);
		if(pg == NULL)
			return NULL;
		
		void *addr = page_addr(pg);
		mc->memcacheNum = manage_memcache(addr, mc->memcacheBuddyOrder, mc->memcacheSize);
		mc->nextcache = addr;
		mc->memcachePageEnd->list.next = &(pg->list);
		mc->memcachePageEnd = buddy_end(pg, mc->memcacheBuddyOrder);
		mc->memcachePageEnd->list.next = NULL;
	}
	
	ret = mc->nextcache;
	mc->nextcache = (void *)(*((u32 *)mc->nextcache));	
	(mc->memcacheNum)--;
	
	return ret;

}

static void *free_obj_memcache(memcache *mc, void *obj)
{
	void *addr = mc->nextcache;
	*((u32 *)obj) = (u32)addr;
	mc->nextcache = obj;
	(mc->memcacheNum)++;
}

static void destroy_memcache(memcache *mc)
{
	u32 order = mc->memcacheBuddyOrder;
	page *spg = mc->memcachePageStart;
	page *epg =  buddy_end(spg, order);
	
	while((epg->list).next != NULL)
	{	
		free_pages(spg, order);

		list_head *lh = epg->list.next;

		spg = list_entry(lh, page, list);

		epg = buddy_end(spg, order);
	}

}

/*
kmalloc
*/

static memcache gmc[SLAB_NUM] = {{0,0,0,NULL,NULL,NULL},};

int kmalloc_init(void)
{	
	int i = 0;
	for(; i < SLAB_NUM; i++)
	{
		if(creat_memcache(&gmc[i], (i + 1) * SLAB_BASE_SIZE) == NULL)
		{
			return -1;
		}		
	}	

	return 0;
}
void *kmalloc(u32 size)
{
	u16 index = size / SLAB_BASE_SIZE;

	if(index > SLAB_NUM)
		return NULL;

	return alloc_obj_memcache(&gmc[index]);

}
void kfree(void *addr)
{
	page *pg = addr_page((u32)addr);
	free_obj_memcache(pg->pmc,addr);
}	
