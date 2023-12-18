/**
 * @file kernel.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief the main class of the Kernel
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef KERNEL_H
#define KERNEL_H

#include <memoryManager.h>
#include <interruptHandler.h>
#include <exceptionHandler.h>
#include <miniUart.h>

enum KernelExitCode{
    ShutdownNone,
    ShutdownHalt,
    ShutdownReboot
};

class Kernel{
public:
    /// constructor
    Kernel();

    /// destructor
    ~Kernel();

    /// initialize the kernel
    KernelExitCode init();

private:
    MemoryManager m_memoryManager;
    InterruptHandler m_interruptHandler;
    ExceptionHandler m_exceptionHandler;
    MiniUART m_miniUART;

    static Kernel *m_pInstance;

    friend class ExceptionHandler;
    friend class InterruptHandler;
    friend class Thread;
};

#endif  // KERNEL_H