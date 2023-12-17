/**
 * @file assert.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief implementation of the __assert_failed method
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <assert.h>


__attribute__ ((optimize(0)))
void __assert_failed(const char *__assertion, const char *__file,
               unsigned int __line, const char *__function)
{
    while(1){}
}