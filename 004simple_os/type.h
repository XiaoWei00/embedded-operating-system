#ifndef _TYPE_H
#define _TYPE_H

#define U32MAX ((u32)~0)
#define U32MIN ((u32)0)
#define S32MAX ((s32)(U32MAX >> 1))
#define S32MIN ((s32)-(S32MAX + 1))

typedef char s8;
typedef short int s16;
typedef int s32;
typedef long long int s64;



typedef unsigned char  u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;






#endif
