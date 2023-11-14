ENTRY(_start)

MEMORY{
    IMAGE (rx) : ORIGIN = 0x80000, LENGTH = 2M
    RAM (rwx) : ORIGIN = 0x00900000, LENGTH = 1024M
}

SECTIONS
{
    .text : {
        *(.boot)
        *(.text*)
        __text_end = .;
    } > IMAGE
    . = ALIGN(4k);
    .rodata : {
        *(.rodata*)
    } > RAM
    . = ALIGN(4k);
    .init_array : {
		__init_start = .;

		KEEP(*(.init_array*))

		__init_end = .;
	} > RAM
    . = ALIGN(4k);

    .ARM.exidx : {
		__exidx_start = .;

		*(.ARM.exidx*)

		__exidx_end = .;
	} > RAM
    . = ALIGN(4k);

    .eh_frame : {
		*(.eh_frame*)
	} > RAM
    .data : {
        *(.data*)
    } > RAM
    . = ALIGN(4k);
    .bss : {
        __bss_start = .;
        *(COMMON*)
        *(.bss)
        __bss_end = .;
        __bss_size = (__bss_end - __bss_start) >> 3;
    } > RAM
   /DISCARD/ : { *(.comment) *(.gnu*) *(.note)}
}
