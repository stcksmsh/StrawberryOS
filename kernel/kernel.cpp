#include "kernel.h"
#include <miniUart.h>

void Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();

    timer_init();

    uart.putChar('0');

    uart << (char*)"Hello World!\n";

    // int j = 0;
    while (1){
        uart.update();
        // uart.putChar('0' + j + cnt);
    }
}