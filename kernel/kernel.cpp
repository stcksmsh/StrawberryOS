#include "kernel.hpp"
#include <miniUart.hpp>
#include <framebuffer.hpp>

int Kernel::init()
{
    MiniUART uart = MiniUART();
    uart.init();
    int machineInfoOut = MachineInfo::getInfo();
    /// block containing init messages:
    /// ASCII art, machine info and device power states
    {
        int lvl = 0;
        __asm__ volatile("mrs %0, CurrentEL" : "=r"(lvl));
        lvl >>= 2;
        uart << (char*)R""""(
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠶⣦⣤⣀⡀⠀⢀⣴⠞⠻⣧⠀⠀⠀⠀⢀⣤⣶⣿⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡆⠀⠀⠈⠙⠳⣾⡇⠀⠀⢹⡇⠀⣠⡴⠟⢉⣹⣿⡀⠀⠀
    ⠀⠀⠀⠀⠀⠀⢀⡤⠖⠋⠙⢿⣆⠀⠉⠉⠒⢌⣳⡄⢀⠀⣷⣞⣥⠶⠛⠋⠉⠉⠀⠀⠀
    ⠀⠀⠀⠀⢀⡴⠋⠀⢀⠤⣦⠀⠙⠳⣤⣀⣀⣀⣙⣿⣼⣴⣿⠿⠗⠶⢶⣤⡀⠀⠀⠀⠀
    ⠀⠀⠀⣠⠏⠀⠀⠀⠸⠿⠋⠀⠀⣠⣾⠿⠋⠡⠼⠻⣿⣿⡿⢏⡉⠑⠢⡉⠻⢷⣤⣀⡀
    ⠀⠀⢠⠏⣠⠚⡷⠀⠀⠐⣤⣴⣾⠛⠁⠀⠀⢀⣤⡾⣿⡀⠉⢢⠙⢦⣤⣤⣤⣶⡿⠛⠁
    ⠀⢀⡏⠀⠛⠛⠁⠀⠀⣀⣀⠉⠛⠿⠿⠿⠿⠟⠋⠀⠸⣷⣤⡀⠣⠈⢿⣯⠁⠀⠀⠀⠀
    ⠀⣸⠁⠀⠀⠀⠀⠀⢰⣁⡼⠀⠀⠀⣀⣀⠀⠀⠀⠀⢀⡈⠻⠿⣶⣦⣼⣿⣇⠀⠀⠀⠀
    ⢀⡏⡴⢳⡄⠀⠀⠀⠈⠉⠀⠀⠀⣸⣅⣸⠆⠀⠀⢰⣇⣽⠀⠀⠀⠀⢠⠲⣿⡄⠀⠀⠀
    ⢸⠃⠿⠟⠀⠀⠀⠀⣴⠋⣧⠀⠀⠈⠉⠉⠀⠀⠀⠈⠛⠋⠀⠀⠀⠀⢸⣤⢿⡇⠀⠀⠀
    ⣾⠀⠀⠀⣠⣄⠀⠀⢻⡾⠃⠀⠀⠀⠀⢠⡤⣤⠀⠀⠀⠀⡴⠛⡦⠀⠈⠁⣾⠃⠀⠀⠀
    ⣿⠀⠀⢰⣧⣼⡇⠀⠀⠀⠀⠀⠀⠀⢰⣿⣤⠞⠀⠀⠀⠀⢿⠾⠃⠀⢀⣼⠏⠀⠀⠀⠀
    ⣿⠀⠀⠀⠛⠁⠀⠀⠀⢠⠖⢲⠀⠀⠀⠉⠀⠀⠀⠀⢀⣀⡀⠀⢀⣴⠿⠁⠀⠀⠀⠀⠀
    ⣿⡄⢠⠤⡀⠀⠀⠀⠀⢺⣴⠟⠀⠀⣠⠖⢲⡄⠀⣰⣏⡸⢃⣴⠟⠁⠀⠀⠀⠀⠀⠀⠀
    ⢻⣷⢸⣀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠶⠛⠀⠀⠈⣩⡾⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⢿⣧⠉⠀⠀⡴⢳⠀⠀⢀⣴⢒⡆⠀⠀⠀⣠⣴⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠈⠻⣷⣄⡀⠷⠛⠀⠀⠘⠿⣟⣡⣤⡶⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠈⠛⠿⢷⣶⣶⣶⡾⠿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    Welcome to Strawberry OS\nCurrent privilege level: EL)"""";
        uart.putChar('0' + lvl);
        uart.putChar('\n');
        
        if(machineInfoOut != 0){
            uart << (char*)"Failed to get machine info\n";
        }else{
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
        }

        Mailbox mb = Mailbox();

        mb.writeBuff(0, 48*4);
        mb.writeBuff(1, MBOX_REQUEST);

        mb.writeBuff(2, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(3, 8);
        mb.writeBuff(4, MBOX_REQUEST);
        mb.writeBuff(5, MBOX_DEVICE_SD_CARD);
        mb.writeBuff(6, 1);

        mb.writeBuff(7, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(8, 8);
        mb.writeBuff(9, MBOX_REQUEST);
        mb.writeBuff(10, MBOX_DEVICE_UART0);
        mb.writeBuff(11, 1);

        mb.writeBuff(12, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(13, 8);
        mb.writeBuff(14, MBOX_REQUEST);
        mb.writeBuff(15, MBOX_DEVICE_UART1);
        mb.writeBuff(16, 1);

        mb.writeBuff(17, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(18, 8);
        mb.writeBuff(19, MBOX_REQUEST);
        mb.writeBuff(20, MBOX_DEVICE_USB_HCD);
        mb.writeBuff(21, 1);

        mb.writeBuff(22, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(23, 8);
        mb.writeBuff(24, MBOX_REQUEST);
        mb.writeBuff(25, MBOX_DEVICE_I2C0);
        mb.writeBuff(26, 1);

        mb.writeBuff(27, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(28, 8);
        mb.writeBuff(29, MBOX_REQUEST);
        mb.writeBuff(30, MBOX_DEVICE_I2C1);
        mb.writeBuff(31, 1);

        mb.writeBuff(32, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(33, 8);
        mb.writeBuff(34, MBOX_REQUEST);
        mb.writeBuff(35, MBOX_DEVICE_I2C2);
        mb.writeBuff(36, 1);

        mb.writeBuff(37, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(38, 8);
        mb.writeBuff(39, MBOX_REQUEST);
        mb.writeBuff(40, MBOX_DEVICE_SPI);
        mb.writeBuff(41, 1);

        mb.writeBuff(42, MBOX_TAG_GET_POWER_STATE);
        mb.writeBuff(43, 8);
        mb.writeBuff(44, MBOX_REQUEST);
        mb.writeBuff(45, MBOX_DEVICE_CCP2TX);
        mb.writeBuff(46, 1);

        mb.writeBuff(47, MBOX_TAG_END);

        if(!mb.call(MBOX_CH_ARM_TO_VC)){
            uart << (char*)"Failed to get device power states\n";
        }else{
            uart << (char*)"SD CARD:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"UART0:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"UART1:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"USB_HCD:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"I2C0:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"I2C1:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"I2C2:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"SPI:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            uart << (char*)"CCP2TX:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
        }
    }
   
    while (1)uart.update();
    return 0;
}