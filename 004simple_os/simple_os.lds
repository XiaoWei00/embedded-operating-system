







SECTIONS
{
	. = 0x30000000;
		
	. = ALIGN(4);
	
	code_start = .;
	
	.text :
	{

	 start.o (.text)
	 clock.o (.text)
	 sdram.o (.text)
	 nandflash.o (.text)
	 level1init.o (.text)
	 main.o  (.text)
	 uart.o  (.text)
	 *(.text)
	 
	}

	. = ALIGN(4);

	.rodata :
	{
	
	   *(.rodata)
	   	
	}

	. = ALIGN(4);

	.data :
	{

		*(.data)
	
	}

	. = ALIGN(4);
		
	bss_start = .;

	.bss :
	{
		*(.bss)
	}

	bss_end = .;
	

}





