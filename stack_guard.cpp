#include <stdint.h>

#define STACK_CHK_GUARD 0x595e9fbd94fda766
// extern "C" uintptr_t __stack_chk_guard;
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void)
{
    // do something
    while(1);
}
