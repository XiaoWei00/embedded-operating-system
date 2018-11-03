#include "memory.h"

static list_head page_buddy[MAX_BUDDY_PAGE_NUM];

static void page_buddy_init(void)
{
	int i =0;
	for(i = 0; i < MAX_BUDDY_PAGE_NUM; i++)
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
				pg->order = (MAX_BUDDY_PAGE_NUM - 1);
			}
			else
			{
				pg->order = -1;
			}	
			list_add_tail(&page_buddy[MAX_BUDDY_PAGE_NUM - 1],&(pg->list));
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
	for(; tmporder < MAX_BUDDY_PAGE_NUM; tmporder++)
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

	for(; order < MAX_BUDDY_PAGE_NUM; order++)
	{
		page *npg = next_buddy(pg, order);
		page *ppg = prev_buddy(pg, order);
		if(((npg->flags & PAGE_BUDDY_BUSY) == 0) && (npg->order == order))
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
		else if(((ppg->flags & PAGE_BUDDY_BUSY) == 0) && (ppg->order == order))
		{
			list_head *pch = &(ppg->list);
			list_head *pct = &(buddy_end(ppg, order)->list);

			list_remove_chain(pch,pct);

			ppg->order = order+1;

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

		list_add_chain_head(&page_buddy[order],&(pg->list), &(buddy_end(pg, order)->list));
	
	}
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
	free_pages(addr_page((u32)addr),order);
}	




