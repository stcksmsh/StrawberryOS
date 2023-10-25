#include "common/gpio.h"
#include "common/uart.h"

void main()
{
    uart_init();
    uart_write("9876543210");

    while (1) uart_update();
}