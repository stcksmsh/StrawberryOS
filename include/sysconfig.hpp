#ifndef SYSCONFIG_H
#define SYSCONFIG_H



#define KLOBYTE			0x400

#define MEGABYTE		0x100000

#define GIGABYTE		0x40000000ULL

#ifndef KERNEL_MAX_SIZE
#define KERNEL_MAX_SIZE		(2 * MEGABYTE)
#endif

#ifndef KERNEL_STACK_SIZE
#define KERNEL_STACK_SIZE	128 * KLOBYTE
#endif

#ifndef CORES
#define CORES 4
#endif

#ifndef EXCEPTION_STACK_SIZE 
#define EXCEPTION_STACK_SIZE 32 * KLOBYTE
#endif

#include <memorymap.hpp>

#endif