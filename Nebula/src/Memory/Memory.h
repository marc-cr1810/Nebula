#ifndef Ne_MEMORY_H
#define Ne_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "port.h"

void* Mem_Alloc(size_t size);
void* Mem_Calloc(size_t elemCount, size_t elemSize);
void* Mem_Realloc(void* ptr, size_t new_size);
void Mem_Free(void* ptr);

#ifdef __cplusplus
}
#endif


#endif