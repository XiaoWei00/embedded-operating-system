



ENTRY(main)

SECTIONS
{
	. = 0X30100000;
	. = ALIGN(4);
	_code_start = .;
	
	.text : 
	{
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







