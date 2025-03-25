OUTPUT_ARCH(arm)
ENTRY(_startapp)
MEMORY
{
    FLASH (rx) : ORIGIN = 0x70008000, LENGTH = 0x00178000
    SRAM (rwx) : ORIGIN = 0x80f60000, LENGTH = 0x000a0000
}
SECTIONS
{
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
 
 /* add own app defined sections here !!! */
 .app_early_init_array :
 {
  PROVIDE (__start_app_early_initcall = .);
  KEEP (*(.app.initcall1.init))
  KEEP (*(.app.initcall2.init))
  PROVIDE (__stop_app_early_initcall = .);
 } > FLASH
 
 .app_late_init_array :
 {
  PROVIDE (__start_app_late_initcall = .);
  KEEP (*(.app.initcall3.init))
  PROVIDE (__stop_app_late_initcall = .);
 } > FLASH
 
 .app_logger_init_array :
 {
  PROVIDE (__start_app_logger_init = .);
  KEEP (*(.app.logger.init))
  PROVIDE (__stop_app_logger_init = .);
 } > FLASH
 
 .app_communication_ops_array :
 {
  PROVIDE (__start_app_comm_ops = .);
  KEEP (*(.app.comm.ops))
  PROVIDE (__stop_app_comm_ops = .);
 } > FLASH
  
 .app_wnet_event_handler_array :
 {
  PROVIDE (__start_wnet_event_handler = .);
  KEEP (*(.wnet.event.handler))
  PROVIDE (__stop_wnet_event_handler = .);
 } > FLASH
 
 .ctors :
 {
  KEEP (*crtbegin.o(.ctors))
  KEEP (*crtbegin?.o(.ctors))
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
  KEEP (*(SORT(.ctors.*)))
  KEEP (*(.ctors))
 } > FLASH
 .dtors :
 {
  KEEP (*crtbegin.o(.dtors))
  KEEP (*crtbegin?.o(.dtors))
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
  KEEP (*(SORT(.dtors.*)))
  KEEP (*(.dtors))
 } > FLASH
 .rodata :
 {
  . = ALIGN(4);
  *(.rodata .rodata.*)
  *(.gnu.linkonce.r.*)
 } > FLASH
 .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
 __exidx_start = .;
 .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH
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
  . = ALIGN(. != 0 ? 32 / 8 : 1);
 } > SRAM
 . = ALIGN(16);
 _bss_end__ = . ;
 __bss_end__ = .;
 __end__ = . ;
 _end = .;
 PROVIDE (end = .);
 ASSERT(SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data) <= LENGTH(FLASH), "!! Text exceed flash size !!")
    ASSERT(SIZEOF(.data) + SIZEOF(.bss) <= LENGTH(SRAM), "!! Data exceed ram size !!")
}
