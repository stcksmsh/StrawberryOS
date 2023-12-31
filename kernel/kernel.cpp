/**
 * @file kernel.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief implementation of the kernel class
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "kernel.h"
#include <miniUart.h>
#include <framebuffer.h>
#include <heapAllocator.h>
#include <sysconfig.h>
#include <machineinfo.h>
#include <assert.h>
#include <bcm2711.h>
#include <interrupt.h>
#include <thread.h>

Kernel *Kernel::m_pInstance = 0;

void test(void* args){
    MiniUART m_miniUART;
    m_miniUART << (char*)"Hello from thread";
    m_miniUART.putChar('\n');
}

Kernel::Kernel():
    m_memoryManager(false), /// DONT USE MMU FOR NOW, IT'S NOT WORKING
    m_interruptHandler(),
    m_exceptionHandler(),
    m_miniUART()
{
    assert(m_pInstance == 0);
    m_pInstance = this;
    m_miniUART.init();
}

Kernel::~Kernel()
{}

void timerPrint(void *pParam)
{
    MiniUART *m_miniUART = reinterpret_cast<MiniUART*>(pParam);
    m_miniUART->putChar('T');
    write32(ARM_SYSTIMER_C0, read32(ARM_SYSTIMER_CLO) + 1000000);
    regSet(ARM_SYSTIMER_CS, 1, 1, IRQ_TIMER_0);
}

void timerInit(){
    write32(ARM_TIMER_CONTROL, 0);
    MiniUART m_miniUART = MiniUART();
    uint64_t time = read32(ARM_SYSTIMER_CLO);
    m_miniUART.printHex(time);
    m_miniUART.putChar('\n');
    write32(ARM_SYSTIMER_C0, read32(ARM_SYSTIMER_CLO) + 1000000);
}

uint64_t getPC(){
    uint64_t lr;
    __asm__ volatile("mov %0, lr" : "=r" (lr));
    return lr;
}

KernelExitCode Kernel::init()
{
    int machineInfoOut = MachineInfo::getInfo();
    /// if we failed to get machine info, exit
    if(machineInfoOut != 0){
        return ShutdownHalt;
    }

    bool intro = false;
    bool heapTest = false;
    bool memTestHeap = false;
    bool sysCallTest = false;
    bool timerTest = false;
    bool threadClassTest = true;
    /// block containing init messages:
    /// ASCII art, machine info and device power states
    if(intro){
        int lvl = 0;
        __asm__ volatile("mrs %0, CurrentEL" : "=r"(lvl));
        int procNum = 0;
        __asm__ volatile("mrs %0, MPIDR_EL1" : "=r"(procNum));
        lvl >>= 2;
        m_miniUART << (char*)R""""(
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
    ⠀⠀⠀⠈⠛⠿⢷⣶⣶⣶⡾⠿⠟⠋⠁)"""";
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Welcome to Strawberry OS";
        m_miniUART.putChar('\n');
        m_miniUART << (char*) "Current privilege level: EL";
        m_miniUART.putChar('0' + lvl);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Processor number: ";
        m_miniUART.putChar('0' + procNum);
        m_miniUART.putChar('\n');
        
        if(machineInfoOut != 0){
            m_miniUART << (char*)"Failed to get machine info\n";
        }else{
            uint64_t memSize = MachineInfo::getMemSize();
            memSize /= 1 << 20;
            m_miniUART << (char*)"RAM: " << memSize << (char*)"MB";
            m_miniUART.putChar('\n');

            m_miniUART << (char*)"MAC: ";
            m_miniUART.printHex(MachineInfo::getMAC());
            m_miniUART.putChar('\n');

            m_miniUART << (char*)"ARM_MEM_START: ";
            m_miniUART.printHex(MachineInfo::getARM_MEM_START());
            m_miniUART.putChar('\n');

            m_miniUART << (char*)"ARM_MEM_END: ";
            m_miniUART.printHex(MachineInfo::getARM_MEM_END());
            m_miniUART.putChar('\n');

            m_miniUART << (char*)"VC_MEM_START: ";
            m_miniUART.printHex(MachineInfo::getVC_MEM_START());
            m_miniUART.putChar('\n');

            m_miniUART << (char*)"VC_MEM_END: ";
            m_miniUART.printHex(MachineInfo::getVC_MEM_END());
            m_miniUART.putChar('\n');
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
            m_miniUART << (char*)"Failed to get device power states\n";
        }else{
            m_miniUART << (char*)"SD CARD:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"UART0:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"UART1:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"USB_HCD:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"I2C0:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"I2C1:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"I2C2:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"SPI:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
            m_miniUART << (char*)"CCP2TX:" << (char*)(mb.readBuff(6) & 0x1 ? "on, " : "off, ")  << (char*)(mb.readBuff(6) & 0x2 ? "doesn't exist" : "exists") << '\n';
        }
        m_miniUART << (char*)"----------------------------------------";
        m_miniUART.putChar('\n');
    }

    /// testing heap allocator
    if(heapTest){
        HeapAllocator heap = HeapAllocator();
        heap.init(MEM_HEAP_START, MEM_HEAP_SIZE);
        m_miniUART << (char*)"Testing heap allocator";
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Free memory: ";
        m_miniUART.printHex(heap.getHeapFreeMemory());
        m_miniUART.putChar('\n');
        int **test = (int**)heap.heapAllocate(sizeof(int*)*100);
        for(int i = 0; i < 100; i++){
            test[i] = (int*)heap.heapAllocate(sizeof(int)*100);
            for(int j = 0; j < 100; j++){
                test[i][j] = i*100 + j;
            }
        }
        int invalid = 0;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(test[i][j] != i*100 + j){
                    invalid++;
                }
            }
            heap.heapFree(test[i]);
        }
        heap.heapFree(test);
        m_miniUART << (char*)"Invalid: " << invalid;
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Free memory: ";
        m_miniUART.printHex(heap.getHeapFreeMemory());
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"----------------------------------------";
        m_miniUART.putChar('\n');
    }

    /// testing memory manager, just the heap stuff
    if(memTestHeap){
        m_miniUART << (char*)"Testing memory manager";
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Free memory: ";
        m_miniUART.printHex(MemoryManager::getMemorySize());
        m_miniUART.putChar('\n');
        int **test = (int**)MemoryManager::heapAllocate(sizeof(int*)*100);
        for(int i = 0; i < 100; i++){
            test[i] = (int*)MemoryManager::heapAllocate(sizeof(int)*100);
            for(int j = 0; j < 100; j++){
                test[i][j] = i*100 + j;
            }
        }
        test = (int**)MemoryManager::heapReallocate(test, sizeof(int*)*200);
        int invalid = 0;
        for(int i = 0; i < 100; i++){
            for(int j = 0; j < 100; j++){
                if(test[i][j] != i*100 + j){
                    invalid++;
                }
            }
            MemoryManager::heapFree(test[i]);
        }
        m_miniUART << (char*)"Invalid: " << invalid;
        m_miniUART.putChar('\n');
        MemoryManager::heapFree(test);
        m_miniUART << (char*)"Free memory: ";
        m_miniUART.printHex(MemoryManager::getMemorySize());
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"----------------------------------------";
        m_miniUART.putChar('\n');
    }

    uint64_t nSCTLR_EL1;
    asm volatile ("mrs %0, sctlr_el1" : "=r" (nSCTLR_EL1));
    m_miniUART.printHex(nSCTLR_EL1);
    m_miniUART.putChar('\n');
    m_miniUART << (char*)"----------------------------------------";
    m_miniUART.putChar('\n');

    /// testing system calls
    if(sysCallTest){
        __asm__ volatile("svc #0");
        __asm__ volatile("svc #352");
        __asm__ volatile("svc #12");
        m_miniUART << (char*)"----------------------------------------";
        m_miniUART.putChar('\n');
    }

    /// testing timer
    if(timerTest){
        write32(ARM_LOCAL_PMU_CONTROL_CLR, ~0);
        write32(ARM_LOCAL_TIMER_CNTRL0, 0xF);
        InterruptHandler::RegisterIRQ(IRQ_TIMER_0, timerPrint, &m_miniUART);
        InterruptHandler::EnableIRQ(IRQ_TIMER_0);
        // timerInit();
        InterruptHandler::EnableIRQs();
    }

    if(threadClassTest){
        uint64_t spsel;
        __asm__ volatile("mrs %0, spsel" : "=r" (spsel));
        m_miniUART << (char*)"SPSEL: ";
        m_miniUART.printHex(spsel);
        m_miniUART.putChar('\n');

        Thread t(true, true, true);
        uint64_t pc = getPC();
        Thread tt(test, &m_miniUART);
        m_miniUART << (char*)"Threads created\n";
        m_miniUART << (char*)"Thread pid: ";
        m_miniUART.printHex(t.pid);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Thread state: ";
        uint16_t *p = (uint16_t*)&t.state;
        m_miniUART.printHex(*p);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Thread context: ";
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"  sp: ";
        m_miniUART.printHex(t.context.sp);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"  lr: ";
        m_miniUART.printHex(t.context.lr);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"      ";
        m_miniUART.printHex(pc);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"  daif: ";
        m_miniUART.printHex(t.context.daif);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"  nzcv: ";
        m_miniUART.printHex(t.context.nzcv);
        m_miniUART.putChar('\n');
        t.context_save();
        m_miniUART << (char*)"New lr: ";
        m_miniUART.printHex(t.context.lr);
        m_miniUART.putChar('\n');
        tt.context.lr = reinterpret_cast<uint64_t>(Thread::funWrapper);
        m_miniUART << (char*)"Test thread lr: ";
        m_miniUART.printHex(tt.context.lr);
        m_miniUART.putChar('\n');
        m_miniUART << (char*)"Tests done";
        m_miniUART.putChar('\n');
        Thread::current_thread = &tt;
        tt.context_load();
    }
    __asm__ volatile("wfi");

    while (1)m_miniUART.update();
    return ShutdownNone;
}