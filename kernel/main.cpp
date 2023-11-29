#include "kernel.h"

extern "C" int main(void){
    Kernel kernel = Kernel();
    return kernel.init();
}