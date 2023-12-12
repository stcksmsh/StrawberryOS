#include <sysconfig.h>
#include <types.h>
#include <util.h>
#include <miniUart.h>

void sysinit(){
    // __asm__ volatile (" cpsie i"); // Enable IRQs 
    // asm volatile ("cpsie f"); // Enable FIQs
    
    // Clear BSS
    extern uint8_t __bss_start;
    extern uint8_t  __bss_size;
    memset(&__bss_start, 0, __bss_size);

    // Call constructors of static objects
    extern void (*__init_start)(void);    
    extern void (*__init_end)(void);
    for(void (**pFunc)(void) = &__init_start; pFunc < &__init_end; pFunc++)
        (**pFunc)();    


    extern int MAINPROC ();    
    MAINPROC();
    int exitValue = 0;
    asm volatile ("mov %0, x0" : "=r"(exitValue));
    MiniUART uart = MiniUART();
    uart.putChar('\n');
    uart.putChar('\n');
    uart.putChar('\n');
    uart.putChar('0' + exitValue);
    // Call destructors of static objects
    extern void (*__fini_start)(void);    
    extern void (*__fini_end)(void);
    for(void (**pFunc)(void) = &__fini_start; pFunc < &__fini_end; pFunc++)
        (**pFunc)();
    while(1){
        asm volatile("wfi");
    }
}