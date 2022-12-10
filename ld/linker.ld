ENTRY(_start)

SECTIONS 
{
	. = 0x8000;

	__start = .;

	__text_start = .;
	.text : 
	{
		*(.text.startup)
		*(.text)
	}
	. = ALIGN(4096);
	__text_end = .;

	. = 0x9000;
	__rodata_start = .;
	.rodata : 
	{
		*(.rodata)
	}
	. = ALIGN(4096);
	__rodata_end = .;

	. = 0xA000;
	__data_start = .;
	.data :
	{
		*(.data)
	}
	. = ALIGN(4096);
	__data_end = .;

	. = 0xC000;
	__bss_start = .;
	.bss :
	{
		*(.bss)
	}
	. = ALIGN(4096);
	__bss_end = .;

	__end = .;

	/DISCARD/ : 
	{
		*(.comment)
	}
}