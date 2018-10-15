
#include "math.h"
#include "type.h"


u64 u64_mul(u64 a, u64 b)
{
   if(b == 0)
   		return 0;
   if(b == 1)
   		return a;

   u64 ret = 0;
   
   while(a--)
   {
	 ret += b;
   }
   
   return ret;
}
s64 s64_mul(s64 a, s64 b)
{
	if(b == 0)
		return 0;
	if(b == 1)
		return 1;
	
	s8 sign = 1;
	s64 ret = 0;
	
	
	if(a < 0)
		a = -a;
	if(b < 0)
		b = -b;
	ret = u64_mul(a,b);

	if(((u64)a >> (sizeof(s64) * 8 -1)) ^ ((u64)b >> (sizeof(s64) * 8 -1))) /*a,bÒìºÅ*/
		ret = - ret;

	return ret;
	
}	
char umul_overflow(u32 a, u32 b)
{
	u64 t = a * b;
	if(u64_mul(a,b) > U32MAX)
		return 1;
	return 0;
}
char mul_overflow(s32 a, s32 b)
{
	if(s64_mul(a,b) > S32MAX || s64_mul(a,b) < S32MAX)
		return 1;
	return 0;
}
unsigned int udiv(unsigned int a,unsigned int b)
{
	if(b == 0)
		return -1;
	if(b == 1)
		return a;

	unsigned int ret = 0;
    unsigned  char overflowFlag = 0;
	while(b <= a)
	{
		unsigned int temp = 1;

		while(b * temp < a)
		{
			temp = temp << 1;/*³ËÒÔ2*/

			if(umul_overflow(b,temp))
			{
				overflowFlag = 1;
				break;
			}	
		}	
		if(b * temp == a && !overflowFlag)
		{
			ret += temp;
			a = 0;
		}
		else
		{
			overflowFlag = 0;
			temp = temp >> 1;
			ret += temp;
		    a = a - b * temp;
		}	
		
		
	}	

	return ret;
}
unsigned int umod(unsigned int a,unsigned int b)
{
	return (a - udiv(a,b) * b);
}	
int div(int a,int b)
{
	if(b == 0)
		return -1; /*´íÎó*/
	int sign = 1;
	int ret = 0;	 
	if((a & (1 << sizeof(int) * 8 - 1)) ^ (b & (1 << sizeof(int) * 8 - 1)))/*a,bÒìºÅ*/
	{
	  sign = -1;		
	}
	if(a < 0) a = -a;
	if(b < 0) b = -b;

	unsigned char overflawFlag = 0;
	while(b <= a)
	{
		int temp = 1;
		
		while((b * temp) < a)
		{
			temp = temp << 1;/*³ËÒÔ2*/
			if(umul_overflow(b,temp))
			{
				overflawFlag = 1;
				break;
			}	
		}
		if((b * temp) == a && !overflawFlag) 
		{
			ret += temp;
			a = 0;
		}
		else
		{	
			overflawFlag = 0;
			temp = temp >> 1;
			ret += temp;
			a = a - b * temp ; 
		}
				
	}
	
	
	return (ret * sign);
	
			
}


int mod(int a,int b)
{
	return (a - div(a,b) * b);
}










