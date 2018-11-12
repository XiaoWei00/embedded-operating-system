#ifndef _TYPE_H
#define _TYPE_H


#define NULL 0

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

#define size_t u32
#define addr_t u32

#define bool s8 
#define FALSE 0
#define TRUE (!FALSE)

/*大端--->小端*/
#define b2s_32_endian(bytes) \
	(u32)( 	\
	((((u32)(bytes)) & (0xff000000U)) >> 24) | 	\
	((((u32)(bytes)) & (0x00ff0000U)) >> 8 ) |	\
    ((((u32)(bytes)) & (0x0000ff00U)) << 8)  |	\
	((((u32)(bytes)) & (0x000000ffU)) << 24)	)	

/*小端--->大端*/
#define s2b_32_endian(bytes) b2s_32_endian(bytes)

#endif
