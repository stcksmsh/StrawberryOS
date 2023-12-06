#include <assert.h>


__attribute__ ((optimize(0)))
void __assert_failed(const char *__assertion, const char *__file,
               unsigned int __line, const char *__function)
{
    while(1){}
}