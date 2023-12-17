/**
 * @file stack_guard.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief implementation of the stack guard, need to randomize the value
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <types.h>

#define STACK_CHK_GUARD 0x595e9fbd94fda766
// extern "C" uintptr_t __stack_chk_guard;
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void)
{
    // do something
    while(1);
}
