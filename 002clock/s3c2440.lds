




SECTIONS
{
	. = 0X00000000;
	. = ALIGN(4);
	_code_start = .;
	
	.text : 
	{
		start.o
		*(.text) 
	}

	. = ALIGN(4);
	.data : 
	{
		*(.data)

	}
	
	. = ALIGN(4);
	.rodata : 
	{
		*(.rodata)

	}
	. = ALIGN(4);
	bss_start = .;
	
	.bss :  
	{
		*(.bss) 
	}

	bss_end = .;
}







