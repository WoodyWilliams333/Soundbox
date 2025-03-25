/***********************************************************************************
*	Copyright (C) 2012
* 
*	Author			: Li.Hua
*	E-Mail     		: lihua_338@163.com
*
***********************************************************************************/

OUTPUT_ARCH(arm)
/* Section Definitions */
ENTRY(_startapp)

MEMORY
{
    FLASH (rx) : ORIGIN = TEXT_BASE, LENGTH = TEXT_SIZE
    SRAM (rwx) : ORIGIN = DATA_BASE, LENGTH = DATA_SIZE
}

SECTIONS
{
	/* first section is .text which is used for code */
	.text :
	{
		__text_start__ = .;
		KEEP(*(.vectors))
		KEEP(*(.FILEINFO))
		CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*)
		KEEP (*(.text.*personality*))
		*(.glue_7t) *(.glue_7) *(.vfp11_veneer)
		KEEP(*(.fini))
		*(.gcc_except_table)
	} > FLASH
	. = ALIGN(4);
   
	.init :
	{
		KEEP (*(.init))
	} > FLASH

	.fini :
	{
		KEEP (*(.fini))
	} > FLASH

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > FLASH
	.init_array :
	{
		 PROVIDE_HIDDEN (__init_array_start = .);
		 KEEP (*(SORT(.init_array.*)))
		 KEEP (*(.init_array))
		 PROVIDE_HIDDEN (__init_array_end = .);
	} > FLASH
	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > FLASH
	.ctors :
	{
		/* gcc uses crtbegin.o to find the start of
		   the constructors, so we make sure it is
		   first.  Because this is a wildcard, it
		   doesn't matter if the user does not
		   actually link against crtbegin.o; the
		   linker won't look for a file to match a
		   wildcard.  The wildcard also means that it
		   doesn't matter which directory crtbegin.o
		   is in.  */
		KEEP (*crtbegin.o(.ctors))
		KEEP (*crtbegin?.o(.ctors))
		/* We don't want to include the .ctor section from
		   the crtend.o file until after the sorted ctors.
		   The .ctor section from the crtend file contains the
		   end of ctors marker and it must be last */
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))
	} > FLASH
	.dtors          :
	{
		KEEP (*crtbegin.o(.dtors))
		KEEP (*crtbegin?.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
	} > FLASH

	/* .rodata section which is used for read-only data (constants) */
	.rodata :
	{
		. = ALIGN(4);
		*(.rodata .rodata.*)
		*(.gnu.linkonce.r.*)
	} > FLASH

	.ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
	__exidx_start = .;
	.ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH
	__exidx_end = .;


	PROVIDE (__etext = .);
	PROVIDE (_etext = .);
	PROVIDE (etext = .);
	__text_end__ = .;
	
	. = ALIGN(4);
	.data : AT(etext)
	{
		__data_start__ = .;
		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
	} > SRAM
	.data1 : { *(.data1) }
	_edata = .; PROVIDE (edata = .);
	__data_end__ = .;			

	__bss_start = .;
	__bss_start__ = .;
	.bss (NOLOAD):
	{
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		/* Align here to ensure that the .bss section occupies space up to
		 _end.  Align after .bss to ensure correct alignment even if the
		.bss section disappears because there are no input sections.
		FIXME: Why do we need it? When there is no .bss section, we don't
		pad the .data section.  */
		. = ALIGN(. != 0 ? 32 / 8 : 1);
	} > SRAM
	. = ALIGN(16);
	_bss_end__ = . ;
	__bss_end__ = .;
	__end__ = . ;
	_end = .;
	PROVIDE (end = .);

	ASSERT(SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data) <= LENGTH(FLASH), "!! Text exceed flash size !!")
    ASSERT(SIZEOF(.data) + SIZEOF(.bss)/* + (LENGTH(SRAM) / 2) + (384*1024) */<= LENGTH(SRAM), "!! Data exceed ram size !!")

}
