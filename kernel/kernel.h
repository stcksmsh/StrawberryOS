#ifndef KERNEL_H
#define KERNEL_H

#include <memoryManager.h>

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
};

#endif  // KERNEL_H