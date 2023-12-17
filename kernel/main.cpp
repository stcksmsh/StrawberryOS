/**
 * @file main.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief nothing to say
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "kernel.h"

extern "C" int main(void){
    Kernel kernel = Kernel();
    return kernel.init();
}