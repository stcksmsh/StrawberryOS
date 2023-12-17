/**
 * @file sysconfig.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief some system configuration constants
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SYSCONFIG_H
#define SYSCONFIG_H



#define KLOBYTE			0x400

#define MEGABYTE		0x100000

#define GIGABYTE		0x40000000ULL

#ifndef KERNEL_MAX_SIZE
#define KERNEL_MAX_SIZE		(2 * MEGABYTE)
#endif

#ifndef KERNEL_STACK_SIZE
#define KERNEL_STACK_SIZE	(128 * KLOBYTE)
#endif

#ifndef CORES
#define CORES 4
#endif

#ifndef MAINPROC
#define MAINPROC main
#endif

#ifndef EXCEPTION_STACK_SIZE 
#define EXCEPTION_STACK_SIZE (32 * KLOBYTE)
#endif

#include <memorymap.h>

#endif  // SYSCONFIG_H