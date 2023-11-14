#include "kernel.h"
#include <miniUart.h>

volatile int cnt = 0;

void incCnt(){
    cnt++;
}
struct timer_regs {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

#define REGS_TIMER ((struct timer_regs *)0x7e003000)

void timer_init(){
    unsigned int timer1_val = REGS_TIMER->counter_lo;
    timer1_val += 1000000;
    REGS_TIMER->compare[1] = timer1_val;
}


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