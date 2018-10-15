




SECTIONS
{
	. = 0X30000000;
	. = ALIGN(4);
	_code_start = .;
	
	.text : 
	{
		start.o  (.text)
		sdram.o   (.text)
		nandflash.o (.text)
		init.o (.text)
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
	_bss_start = .;
	
	.bss :  
	{
		*(.bss) 
	}

	_end = .;
}







