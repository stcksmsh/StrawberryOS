#include <sysconfig.h>
#include <stdint.h>
#include <util.h>

void sysinit(){
    // asm volatile ("cpsie i"); // Enable IRQs 
    // asm volatile ("cpsie f"); // Enable FIQs
    
    // Clear BSS
    extern unsigned char __bss_start;
    extern unsigned char __bss_size;
    memset(&__bss_start, 0, __bss_size);

    // Call constructors of static objects
    // extern void (*__init_start)(void);    
    // extern void (*__init_end)(void);
    // for(void (**pConstrcut)(void) = &__init_start; pConstrcut <= &__init_end; pConstrcut++)
    //     (**pConstrcut)();    

    asm volatile("b _ZN6Kernel4initEv"); // Call Kernel::init()
}