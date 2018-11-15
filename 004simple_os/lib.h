
#ifndef _LIB_H_
#define _LIB_H_

#include "type.h"
/*

printf(const char *fmt,...)

*/
#define _INTSIZEOFF(n) ((sizeof(n) + sizeof(int) - 1 ) &  ~(sizeof(int) - 1))

typedef char * va_list;
#define va_start(arg,fmt) arg = ((va_list)&fmt + _INTSIZEOFF(fmt))
#define va_arg(ap,v)	*((v *)((ap += _INTSIZEOFF(v)) - _INTSIZEOFF(v)))
#define va_end(ap) ap = (va_list)0


int printfk(const char *fmt,...);


typedef void (*p_putstr)(const char *);


extern p_putstr out_str;


/*
debug
*/
#define INFO 1

void info(char * information);
/*
list

通用链表
*/
typedef struct list_head_t list_head;

struct list_head_t
{
	list_head *prev;
	list_head *next;
};

#define memberoffset(type, member)  ((u32)&(((type *)0)->member))

#define list_for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)

/*宏定义，不能进行类型检查*/
//#define list_entry(ptr, type, member) (type *)((char *)(ptr) - memberoffset(type,member))

#define list_entry(ptr, type, member) \
	({  const typeof(((type *)0)->member) *mptr = (ptr); \
		(type *)((char *)mptr - memberoffset(type, member));})  	
/*
typeof GNU C 标准中的 typeof 关键字
typeof 是自动推导后面 ( ) 里的数据类型
*/

void listhead_init(list_head * list);
void list_add_head(list_head * head, list_head * newnode);
void list_add_tail(list_head * head, list_head * newnode);
void list_add_chain_head(list_head * head, list_head * ch, list_head * ct);
void list_add_chain_tail(list_head * head, list_head * ch, list_head * ct);
void list_remove_chain(list_head * ch, list_head * ct);



/*
memory
*/
void *memcpy(const void *src, void *des, u32 size);
void *memset(void * des, s32 val, size_t size);
/*
string
*/

u32 strlen(const char *str);
s32 strcmp(const char * str1, const char * str2);


#endif






