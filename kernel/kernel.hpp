#ifndef KERNEL_HEADER
#define KERNEL_HEADER

#include <machineinfo.hpp>

class Kernel{
private:
    /// initialize the kernel
    int init();

    /// information on the machine the kernel runs on
    MachineInfo m_machineInfo;
};

#endif