#ifndef Ne_PORT_H
#define Ne_PORT_H

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#ifdef MS_WINDOWS

typedef int8_t    Ne_int8_t;
typedef int16_t   Ne_int16_t;
typedef int32_t   Ne_int32_t;
typedef int64_t   Ne_int64_t;

typedef uint8_t   Ne_uint8_t;
typedef uint16_t  Ne_uint16_t;
typedef uint32_t  Ne_uint32_t;
typedef uint64_t  Ne_uint64_t;

#else

typedef __int8_t    Ne_int8_t;
typedef __int16_t   Ne_int16_t;
typedef __int32_t   Ne_int32_t;
typedef __int64_t   Ne_int64_t;

typedef __uint8_t   Ne_uint8_t;
typedef __uint16_t  Ne_uint16_t;
typedef __uint32_t  Ne_uint32_t;
typedef __uint64_t  Ne_uint64_t;

#endif

typedef float       Ne_float_t;
typedef double      Ne_double_t;

typedef intptr_t Ne_intptr_t;
typedef Ne_intptr_t Ne_size_t;
typedef Ne_size_t Ne_hash_t;


/* Largest possible value of size_t. */
#define NE_SIZE_MAX SIZE_MAX

/* Largest positive value of type Ne_size_t. */
#define NE_SIZE_T_MAX ((NE_size_t)(((size_t)-1)>>1))
/* Smallest negative value of type Ne_size_t. */
#define NE_SIZE_T_MIN (-NE_SIZE_T_MAX-1)

#define NE_CHARMASK(c) ((unsigned char)((c) & 0xFF))

/* Below "a" is a power of 2. */
/* Round down size "n" to be a multiple of "a". */
#define NE_SIZE_ROUND_DOWN(n, a) ((size_t)(n) & ~(size_t)((a) - 1))
/* Round up size "n" to be a multiple of "a". */
#define NE_SIZE_ROUND_UP(n, a) (((size_t)(n) + (size_t)((a) - 1)) & ~(size_t)((a) - 1))
/* Round pointer "p" down to the closest "a"-aligned address <= "p". */
#define NE_ALIGN_DOWN(p, a) ((void *)((uintptr_t)(p) & ~(uintptr_t)((a) - 1)))
/* Round pointer "p" up to the closest "a"-aligned address >= "p". */
#define NE_ALIGN_UP(p, a) ((void *)(((uintptr_t)(p) + (uintptr_t)((a) - 1)) & ~(uintptr_t)((a) - 1)))
/* Check if pointer "p" is aligned to "a"-bytes boundary. */
#define NE_IS_ALIGNED(p, a) (!((uintptr_t)(p) & (uintptr_t)((a) - 1)))

#ifndef NeAPI_FUNC
#   define NeAPI_FUNC(RTYPE) RTYPE
#endif
#ifndef NeAPI_DATA
#   define NeAPI_DATA(RTYPE) extern RTYPE
#endif

#endif
