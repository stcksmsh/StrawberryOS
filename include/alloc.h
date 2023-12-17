/**
 * @file alloc.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief simple memory management, only temporary
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef ALLOC_H
#define ALLOC_H

#include <types.h>

/// Allocates memory
void *malloc(size_t nSize);

/// Frees memory
void free(void *pAddress);

/// Allocates memory and sets it to zero
void *calloc(size_t nSize, size_t nCount);

/// Reallocates memory
void *realloc(void *pAddress, size_t nSize);

/// Allocates a page
void *palloc();

/// Frees a page
void pfree(void *pAddress);

#endif // ALLOC_H