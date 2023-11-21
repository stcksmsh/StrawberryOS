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

    /// SOMETHING HANGS HERE!!!
    // FrameBuffer fb = FrameBuffer(1920, 1080, 32);
    // fb.clear();

    Mailbox mb = Mailbox();
    mb.clearBuff();
    mb.writeBuff(0, 12 * 4);
    mb.writeBuff(1, MBOX_REQUEST);
    
    mb.writeBuff(2, MBOX_TAG_SET_LED);
    mb.writeBuff(3, 8);
    mb.writeBuff(4, MBOX_REQUEST);
    mb.writeBuff(5, MBOX_POWER_LED_PIN);
    mb.writeBuff(6, 1);

    mb.writeBuff(7, MBOX_TAG_SET_LED);
    mb.writeBuff(8, 8);
    mb.writeBuff(9, MBOX_REQUEST);
    mb.writeBuff(10, MBOX_STATUS_LED_PIN);
    mb.writeBuff(11, 1);

    mb.writeBuff(12, MBOX_TAG_END);
    uart <<  (char*)(mb.call(MBOX_CHANNEL_ARM_TO_VC) ? "true" : "false");
    while (1)uart.update();

    return 0;
}