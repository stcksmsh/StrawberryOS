/**
 * @file thread.h`
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief definition of the thread class which is used to store the context of )
 * @version 0.1
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#ifndef THREAD_H
#define THREAD_H

#include <types.h>
#include <cdefs.h>

class Thread{
public:

    Thread( bool is_interruptable = true, 
            bool is_joinable = true,
            bool is_kernel_thread = false);

    Thread(const Thread& other) = delete;

    Thread( void (*entry_point)(void*),
            void* arg,
            bool is_interruptable = true, 
            bool is_joinable = true,
            bool is_kernel_thread = false);

    void context_save();

    void context_load();

private:
    struct ThreadContext
    {
        /// @brief general purpose registers
        uint64_t x19, x20, x21, 
                 x22, x23, x24, x25, x26, x27, x28;
        /// @brief frame pointer, also x29
        uint64_t fp;
        /// @brief link register, also x30
        uint64_t lr;
        /// @brief stack pointer, also x31
        uint64_t sp;
        /// @brief data access interrupt flags
        uint64_t daif;
        /// @brief negative, zero, carry, overflow flags
        uint64_t nzcv;
        /// @brief system control register
        // uint64_t sctlr_el1;

    } PACKED context;


    /// @brief flags representing the state of the thread, done this way to save memory
    struct ThreadState{
        uint16_t    is_running:1,
                    is_ready:1,
                    is_blocked:1,
                    is_suspended:1,
                    is_terminated:1,
                    is_interruptable:1,
                    is_detached:1,
                    is_joinable:1,
                    is_kernel_thread:1;

    } PACKED state;

    /// @brief unique identifier of the thread
    pid_t pid;

    void (*entry_point)(void*);
    void* arg;

    static Thread* current_thread;

    static void funWrapper();

    static pid_t next_pid;

    friend class Kernel;
};


#endif // THREAD_H