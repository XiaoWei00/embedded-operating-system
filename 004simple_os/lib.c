
#include "math.h"
#include "lib.h"
/*


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

