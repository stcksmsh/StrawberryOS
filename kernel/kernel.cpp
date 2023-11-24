#include "kernel.hpp"
#include <miniUart.hpp>
#include <framebuffer.hpp>

int Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();

    int lvl = 0;
    __asm__ volatile("mrs %0, CurrentEL" : "=r"(lvl));
    lvl >>= 2;
    uart << (char*)"Welcome, current privilege level: EL";
    uart.putChar('0' + lvl);
    uart.putChar('\n');
    
    if(MachineInfo::getInfo() != 0)
        uart << (char*)"Failed to get machine info\n";
    uint64_t memSize = MachineInfo::getMemSize();
    memSize /= 1 << 20;
    uart << (char*)"RAM: " << memSize << (char*)"MB";
    uart.putChar('\n');

    uart << (char*)"MAC: ";
    uart.printHex(MachineInfo::getMAC());
    uart.putChar('\n');

    uart << (char*)"ARM_MEM_START: ";
    uart.printHex(MachineInfo::getARM_MEM_START());
    uart.putChar('\n');

    uart << (char*)"ARM_MEM_END: ";
    uart.printHex(MachineInfo::getARM_MEM_END());
    uart.putChar('\n');

    uart << (char*)"VC_MEM_START: ";
    uart.printHex(MachineInfo::getVC_MEM_START());
    uart.putChar('\n');

    uart << (char*)"VC_MEM_END: ";
    uart.printHex(MachineInfo::getVC_MEM_END());
    uart.putChar('\n');

    while (1)uart.update();

    return 0;
}