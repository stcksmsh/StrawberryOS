/**
 * @file assert.h
 * @author Kosta Vukicevic (vukicevickosta@gmail.com)
 * @brief defines assert macro
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ASSERT_H
#define ASSERT_H

#include <cdefs.h>

extern void __assert_fail (const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function)
     __THROW NORETURN;

#ifdef NDEBUG

#define assert(ignore) ((void)0)

#else

#define assert(expr) \
    (static_cast<bool>(expr)\
    ? void(0) \
    : void(0) \
    )
//    : __assert_fail(#expr, __FILE__, __LINE__, __func__) instead of second void(0), but it is not implemented yet

#endif // NDEBUG

#endif // ASSERT_H