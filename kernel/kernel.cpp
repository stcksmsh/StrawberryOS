#include "kernel.h"
#include <miniUart.h>

int Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();

    int lvl = 0;
    __asm__ volatile("mrs %0, CurrentEL" : "=r"(lvl));
    lvl >>= 2;
    uart << (char*)"Welcome, current privilege level: EL";
    uart.putChar('0' + lvl);

    while (1)uart.update();
    return 1;
}