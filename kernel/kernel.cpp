#include "kernel.h"
#include <miniUart.h>

void Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();
    
    int lvl = 0;
    __asm__ volatile("mrs %0, CurrentEL" : "=r"(lvl));
    lvl >>= 2;
    uart.putChar('0' + lvl);

    uart << (char*)"Hello World!\n";

    while (1)uart.update();
}