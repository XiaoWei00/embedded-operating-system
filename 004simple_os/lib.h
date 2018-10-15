
#ifndef _LIB_H_
#define _LIB_H_

#define NULL 0
/*
printf(const char *fmt,...)
*/
/*
可变参数
*/
#define _INTSIZEOFF(n) ((sizeof(n) + sizeof(int) - 1 ) &  ~(sizeof(int) - 1))

typedef char * va_list;
#define va_start(arg,fmt) arg = ((va_list)&fmt + _INTSIZEOFF(fmt))
#define va_arg(ap,v)	*((v *)((ap += _INTSIZEOFF(v)) - _INTSIZEOFF(v)))
#define va_end(ap) ap = (va_list)0

int printfk(const char *fmt,...);


typedef void (*p_putstr)(const char *);


extern p_putstr out_str;

#endif



