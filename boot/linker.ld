ENTRY(.start)
SECTIONS
{
    . = 0x80000;
    .text BLOCK(4k) : ALIGN(4k){
        *(.boot)
        *(.text)
    }
    .rodata BLOCK(4k) : ALIGN(4k){
        *(.rodata)
    }
    .data BLOCK(4k) : ALIGN(4k){
        *(.data)
    }
    .bss BLOCK(4k) : ALIGN(4k){
        __bss_start = .;
        *(COMMON)
        *(.bss)
        __bss_end = .;
        __bss_size = (__bss_end - __bss_start) >> 3;
    }    
   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
