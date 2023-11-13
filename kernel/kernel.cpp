#include "kernel.h"
#include <miniUART.h>

void Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();

    uart << (char*)"Hello World!\n";

    while (1) uart.update();
}