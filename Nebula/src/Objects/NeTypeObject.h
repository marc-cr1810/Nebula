#ifndef Ne_TYPEOBJECT_H
#define Ne_TYPEOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "port.h"
#include "Objects/NeObject.h"

typedef NeObject* (*strRepr)(NeObject*);
typedef Ne_hash_t (*hashFunc)(NeObject*);
typedef void (*freefunc)(void*);
typedef void (*destructor)(NeObject*);

typedef struct _type_object
{
    NeVarObject_HEAD;

    const char* typ_name;
    const char* typ_doc;
    Ne_size_t typ_size;
    Ne_size_t typ_itemSize;

    unsigned long typ_flags;

    // Methods
    strRepr typ_strRepr;
    hashFunc typ_hash;
    destructor typ_dealloc;

    struct _type_object* typ_base;
    freefunc typ_free;
} NeTypeObject;

#define NeTypeObject_CAST(op) ((NeTypeObject*)(op))
#define NeTypeObject_CAST_CONST(op) ((const NeTypeObject*)(op))

/*
 *  Functions
*/

int NeTypeObject_Ready(NeTypeObject* type);

static inline int NeTypeObject_IsType(const NeObject* obj, const NeTypeObject* type) { return NeObject_TYPE(obj) == type; }
#define NeTypeObject_IS_TYPE(obj, type) NeTypeObject_IsType(NeObject_CAST_CONST(obj), type)

int NeTypeObject_IsSubtype(const NeTypeObject* a, const NeTypeObject* b);
#define NeTypeObject_IS_SUBTYPE(obj_a, obj_b) NeTypeObject_IsSubtype(NeTypeObject_CAST_CONST(obj_a), NeTypeObject_CAST_CONST(obj_b))

#define NeTypeObject_TypeCheck(obj, type) (NeTypeObject_IS_TYPE(obj, type) || NeTypeObject_IS_SUBTYPE(NeObject_TYPE(obj), type))

/*
 *	Type object flags
*/

/* Set if the type object is dynamically allocated */
#define TPFLAGS_HEAPTYPE (1UL << 9)

/* Set if the type allows subclassing */
#define TPFLAGS_BASETYPE (1UL << 10)

/* Set if the type is 'ready' -- fully initialized */
#define TPFLAGS_READY (1UL << 12)

/* Set while the type is being 'readied', to prevent recursive ready calls */
#define TPFLAGS_READYING (1UL << 13)

/* Objects support garbage collection */
#define TPFLAGS_HAVE_GC (1UL << 14)

/* These flags are used to determine if a type is a subclass. */
#define TPFLAGS_LONG_SUBCLASS        (1UL << 24)
#define TPFLAGS_LIST_SUBCLASS        (1UL << 25)
#define TPFLAGS_TUPLE_SUBCLASS       (1UL << 26)
#define TPFLAGS_BYTES_SUBCLASS       (1UL << 27)
#define TPFLAGS_UNICODE_SUBCLASS     (1UL << 28)
#define TPFLAGS_DICT_SUBCLASS        (1UL << 29)
#define TPFLAGS_BASE_EXC_SUBCLASS    (1UL << 30)
#define TPFLAGS_TYPE_SUBCLASS        (1UL << 31)

#define TPFLAGS_DEFAULT 0


#ifdef __cplusplus
}
#endif

#endif