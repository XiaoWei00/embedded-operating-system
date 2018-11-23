
#include "math.h"
#include "lib.h"
/*
内核打印
*/
p_putstr out_str = NULL ;

#define PBUFFMAX 30
static char printBuffer[PBUFFMAX];
static unsigned char printFlag;/*0---29*/

#define  pbuff_isfull() (printFlag > 28 ? 1 : 0)

static int int2str(int n,char p[],int d)
{
	int ret = 0;

	if(n < 0)
	{
		printBuffer[printFlag++] = '-';	
		n = -n;
	}

		
	while(n)
	{
		 int t = mod(n,d);
		 
          if(d == 16 && t > 9)
 		 {	
			
	  		p[ret] = (char)(t - 10 + 'a');

		 }
		 else
		 {
			p[ret] = (char)(t + '0');
 		 }

		 n = div(n,d);
		 ret++;	  	
	}
	
	return ret--; 			
}

static int uint2str(unsigned int n,char p[])
{
	int ret = 0;
		
	while(n)
	{
		p[ret] = (char)((umod(n,10)) + '0') ;
		n = udiv(n,10);
		ret++;	 
	}
	
	return ret--; 			
}

static void str_to_pbuffer(int count,char s[])
{
	while(count)
 	{
		printBuffer[printFlag++] = s[--count];
		if(pbuff_isfull())
		{	
		  break;
		}
		
	}	
}

static void transform_dxo(va_list arg,int d)
{
		int tmp = va_arg(arg,int);
		char s[10] = {0};
		
		int count = int2str(tmp,s,d); 
 		/*字符串--->buff*/
	 	str_to_pbuffer(count,s);		
		
}

int printfk(const char *fmt,...)
{

	if(fmt == NULL)
		return 0;	

	va_list arg;
	va_start(arg,fmt);


	int i = 0;
	while(fmt[i] != '\0')
	{
		if(fmt[i] != '%')
		{
			/*无%,直接输出*/
			printBuffer[printFlag++] = fmt[i];
		}
		else /*处理%*/
		{
			i++; /*跳过%*/

			switch(fmt[i])
			{
				case 'c':
					printBuffer[printFlag++] = va_arg(arg,char);
					break;
				case 's':
					{	
						char *tmp = va_arg(arg,char *);
						while(*tmp != '\0')
						{
							printBuffer[printFlag++] = *tmp++;
							
							if(pbuff_isfull())
							{	
							  break;
							}							
						}
						
					}
					break;
					
				case 'u':
					{
						unsigned int tmp = va_arg(arg,unsigned int);
						char s[10]={0};
						/*整数转字符串*//*字符串--->buff*/
					   	int count = uint2str(tmp,s); 
					 	str_to_pbuffer(count,s);
					}
					break;
				case 'd':
					transform_dxo(arg,10);
					break;
				case 'x':	
				    transform_dxo(arg,16);
					break;
				case 'o':
					transform_dxo(arg,8);
					break;		

				defult:
					printBuffer[printFlag++] = fmt[i];

			}	
		}
		i++;
		
		if(pbuff_isfull())
		{
			break;
		}

	}

	printBuffer[printFlag] = '\0';  /*缓冲区补字符串尾*/

	out_str(printBuffer);

	printFlag = 0; /*缓冲区清空*/

	va_end(arg);

	return 1;

}

/*
debug
*/
void info(char *information)
{
	#if INFO 
	printfk(information);
	printfk("\r\n");
	#endif
}



void stack_print(u32 sp,s8 sign)
{
	u32 *psp = (u32 *)sp;
	
	printfk("spaddr=%x\r\n",(u32)psp);
	
	u32 i = 0;
	for(i = 0; i <= 16; i++)
	{
		if(sign == 1)
		{	
			printfk("+sp=%x\r\n",*(psp + i));
		}
		else
		{
			printfk("-sp=%x\r\n",*(psp - i));
		}	
	}
}	





/*
list
通用链表
*/

void listhead_init(list_head *list)
{
	list->next = list;
	list->prev = list;
}
static void list_add(list_head *newnode, list_head *next, list_head *prev)
{
		newnode->prev = prev;
		newnode->next = next;

		prev->next = newnode;
		next->prev = newnode;
}
void list_add_head(list_head *head, list_head *newnode)
{
	list_add(newnode,head->next,head);
}
void list_add_tail(list_head *head, list_head *newnode)
{
	list_add(newnode,head,head->prev);
}
void list_del(list_head *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}	
u8 list_empty(const list_head *head)
{
	return head->next == head;
}

void list_add_chain_head(list_head *head, list_head *ch, list_head *ct)
{
	head->next->prev = ct;
	ct->next = head->next;
	
	head->next = ch;
	ch->prev = head;
	
}
void list_add_chain_tail(list_head *head, list_head *ch, list_head *ct)
{
	head->prev->next = ch;
	ch->prev = head->prev;
	ct->next = head;
	head->prev = ct;
}

void list_remove_chain(list_head *ch, list_head *ct)
{
	ch->prev->next = ct->next;
	ct->next->prev = ch->prev;
}

/*
mem
*/
void *memcpy(const void *src, void *des, u32 size)
{
	if(src ==NULL || des == NULL)
		return NULL;

	s8 *sr = (s8 *)src;
	s8 *de = (s8 *)des;
	while(size--)
	{
		*de++ = *sr++;
	}
	return des;
}

void *memset(void *des,s32 val,size_t size)
{
	if(des == NULL || size < 0)
		return NULL;
	char *tmpdes = (char *)des;

	while(size > 0)
	{
		*tmpdes++ = val;
		size--;
	}	

	return des;

}
/*
string
*/

u32 strlen(const char *str)
{
	
	if(str == NULL)
		return 0;	

	u32 count = 0;

	while(*str++ != '\0')
	{
		count++;
	}	
	return count;
}

s32 strcmp(const char *str1,const char *str2)
{	
	if(str1 == NULL && str2 == NULL)
		return 0;
	if(str1 == NULL)
		return -1;
	if(str2 == NULL)
		return 1;

	u32 i = 0, j = 0;
	while(!(str1[i] == '\0' || str2[j] == '\0'))
	{
		if(str1[i] > str2[j])
		{
			return 1;
		}
		else if(str1[i] < str2[j])
		{
			return -1;
		}	
		i++;
		j++;
	}	
	if(str1[i] == '\0' && str2[j] == '\0')
		return 0;
	if(str1[i] == '\0')
	{
		return -1;
	}
	else
	{
		return 1;
	}	
	
}
