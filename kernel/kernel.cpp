#include "kernel.h"
#include <miniUart.h>

void Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();

    uart << (char*)"Hello World!\n";

    while (1) uart.update();
}