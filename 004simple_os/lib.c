
#include "math.h"
#include "lib.h"
/*
ÄÚºË´òÓ¡
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
 		/*×Ö·û´®--->buff*/
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
			/*ÎŞ%,Ö±½ÓÊä³ö*/
			printBuffer[printFlag++] = fmt[i];
		}
		else /*´¦Àí%*/
		{
			i++; /*Ìø¹ı%*/

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
						/*ÕûÊı×ª×Ö·û´®*//*×Ö·û´®--->buff*/
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

	printBuffer[printFlag] = '\0';  /*»º³åÇø²¹×Ö·û´®Î²*/

	out_str(printBuffer);

	printFlag = 0; /*»º³åÇøÇå¿Õ*/

	va_end(arg);

	return 1;

}

/*

Í¨ÓÃÁ´±í

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


