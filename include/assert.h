/**
 * @file assert.h
 * @author Kosta Vukicevic (vukicevickosta@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ASSERT_H
#define ASSERT_H

#define __THROW noexcept(true)

extern "C" void __assert_failed(const char *__assertion, const char *__file,
			   unsigned int __line, const char *__function);


#define assert(expr) \
    (static_cast<bool>(expr)\
    ? void(0) \
    : __assert_failed(#expr, __FILE__, __LINE__, __PRETTY_FUNCTION__) \
    )

#endif // ASSERT_H