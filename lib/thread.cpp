#include <thread.h>
#include "../kernel/kernel.h"

pid_t Thread::next_pid = 0;

Thread* Thread::current_thread = 0;

Thread::Thread(bool is_interruptable, bool is_joinable, bool is_kernel_thread){
    pid = 0;
    state.is_running = 0;
    state.is_ready = 1;
    state.is_blocked = 0;
    state.is_suspended = 0;
    state.is_terminated = 0;
    state.is_interruptable = 0;
    state.is_detached = 0;
    state.is_joinable = is_joinable;
    state.is_kernel_thread = is_kernel_thread;
    context_save();
}

Thread::Thread(void (*entry_point)(void*), void* arg, bool is_interruptable, bool is_joinable, bool is_kernel_thread){
    this->entry_point = entry_point;
    this->arg = arg;

    pid = next_pid++;
    state.is_running = 0;
    state.is_ready = 1;
    state.is_blocked = 0;
    state.is_suspended = 0;
    state.is_terminated = 0;
    state.is_interruptable = 0;
    state.is_detached = 0;
    state.is_joinable = is_joinable;
    state.is_kernel_thread = is_kernel_thread;

    context.fp = 0;
    context.sp = 0;
    context.daif = 0;
    context.nzcv = 0;
    
    context.lr = (uint64_t)funWrapper;
}

void Thread::funWrapper(){
    current_thread->entry_point(current_thread->arg);
}

void Thread::context_save(){
    __asm__ volatile("stp x0, x19, [%0, #0x0]" : : "r" (&context));
    __asm__ volatile("stp x20, x21, [%0, #0xa0]" : : "r" (&context));
    __asm__ volatile("stp x22, x23, [%0, #0xb0]" : : "r" (&context));
    __asm__ volatile("stp x24, x25, [%0, #0xc0]" : : "r" (&context));
    __asm__ volatile("stp x26, x27, [%0, #0xd0]" : : "r" (&context));
    __asm__ volatile("stp x28, x29, [%0, #0xe0]" : : "r" (&context));
    __asm__ volatile("mov %0, sp" : "=r" (context.sp));
    __asm__ volatile("mov %0, lr" : "=r" (context.lr));
    __asm__ volatile("mrs %0, daif" : "=r" (context.daif));
    __asm__ volatile("mrs %0, nzcv" : "=r" (context.nzcv));
}

void Thread::context_load(){
    Kernel::m_pInstance->m_miniUART << (char*)"Loading context, next stop: ";
    Kernel::m_pInstance->m_miniUART.printHex(context.lr);
    Kernel::m_pInstance->m_miniUART.putChar('\n');
    __asm__ volatile("ldp x19, x20, [%0, #0x0]" : : "r" (&context));
    __asm__ volatile("ldp x21, x22, [%0, #0xa0]" : : "r" (&context));
    __asm__ volatile("ldp x23, x24, [%0, #0xb0]" : : "r" (&context));
    __asm__ volatile("ldp x25, x26, [%0, #0xc0]" : : "r" (&context));
    __asm__ volatile("ldp x27, x28, [%0, #0xd0]" : : "r" (&context));
    __asm__ volatile("mov fp , %0" : : "r" (context.fp));
    __asm__ volatile("mov sp, %0" : : "r" (context.sp));
    Kernel::m_pInstance->m_miniUART << (char*)"Warping now...";
    __asm__ volatile("mov lr, %0" : : "r" (context.lr));
    // __asm__ volatile("msr daif, %0" : : "r" (context.daif));
    // __asm__ volatile("msr nzcv, %0" : : "r" (context.nzcv));
    __asm__ volatile("ret");
}