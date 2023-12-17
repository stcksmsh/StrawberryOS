/**
 * @file cdefs.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief defines some common macros
 * @version 0.1
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CDEFS_H
#define CDEFS_H

#define __CONCAT(x, y) x ## y
#define __STRING(x) #x

#define PACKED      __attribute__((packed))
#define MAXALIGN    __attribute__((aligned))
#define ALIGN(n)    __attribute__((aligned(n)))
#define NORETURN    __attribute__((noreturn))
#define NOOPT       __attribute__((optimize(0)))
#define STDOPT      __attribute__((optimize(3)))
#define WEAK        __attribute__((weak))
#define BIT(n)      (1 << (n))
#define IS_POWEROF_2(num) ((num) != 0 && (((num) & ((num) - 1)) == 0))
#define __THROW noexcept(true)

#endif // CDEFS_H
