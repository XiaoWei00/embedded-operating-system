
#include "nandflash.h"


static int IsBootFromNorFlash(void)
{

	/*��0��ַд��*/
	volatile unsigned int *src = (volatile unsigned int *)0;

	unsigned int backup = *src ;

	*src = 0x12345678;

	if( *src == 0x12345678)
	{
 		/*0��ַд���ɹ���nandflash����*/
		*src = backup;
		return 0;
	}
	else
	{
		/*nor flash����*/
		return 1;
	}


}

void copy2sdram(void)
{
	extern int _code_start, _bss_start;

	volatile unsigned int *dest = (volatile unsigned int *)&_code_start;
	volatile unsigned int *end = (volatile unsigned int *)&_bss_start;
	volatile unsigned int *src = (volatile unsigned int *)0;

	unsigned int len = (end - dest ) * sizeof(int) ;
	if(IsBootFromNorFlash())
	{
		/*nor Flash ����*/
		while (dest < end)
		{
			*dest++ = *src++;
		}
	}
	else
	{
	 	/*nand flash ����*/
		nandflash_read(0, (char *)dest,len);

	}
}

void bss_init(void)
{

	extern int _end, _bss_start;
	
	volatile unsigned int *start = (volatile unsigned int *)&_bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;


	while (start <= end)
	{
		*start++ = 0;
	}

}










