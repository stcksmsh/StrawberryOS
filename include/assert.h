/*
 *  assert.h
 * 
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 *
 *  assert macro for checking conditions at runtime
 */

#ifndef ASSERT_H
#define ASSERT_H


// extern "C" void __assert_failed(const char *__assertion, const char *__file,
// 			   unsigned int __line, const char *__function){
//                 while(1);
//                }

#define __THROW noexcept(true)

#define assert(expr) \
    (static_cast<bool>(expr) \
    ? void(0) \
    : void(0) \
    )

    // : __assert_failed(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__) \
    // )

#endif // ASSERT_H