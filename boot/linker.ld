ENTRY(_start)

SECTIONS
{
    . = 0x80000;
    .text : {
        *(.boot)
        *(.text*)
        __text_end = .;
    }
    . = ALIGN(4k);
    .rodata : {
        *(.rodata*)
    }
    . = ALIGN(4k);
    .init_array : {
		__init_start = .;

		KEEP(*(.init_array*))

		__init_end = .;
	}
    . = ALIGN(4k);
    .fini_array : {
		__fini_start = .;

		KEEP(*(.fini_array*))

		__fini_end = .;
	}
    . = ALIGN(4k);
    .ARM.exidx : {
		__exidx_start = .;

		*(.ARM.exidx*)

		__exidx_end = .;
	}
    . = ALIGN(4k);

    .eh_frame : {
		*(.eh_frame*)
	}
    .data : {
        *(.data*)
    }
    . = ALIGN(4k);
    .bss : {
        __bss_start = .;
        *(COMMON*)
        *(.bss)
        __bss_end = .;
        __bss_size = (__bss_end - __bss_start) >> 3;
    }
   /DISCARD/ : { *(.comment) *(.gnu*) *(.note)}
}
