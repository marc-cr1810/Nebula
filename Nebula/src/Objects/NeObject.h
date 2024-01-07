#ifndef Ne_OBJECT_H
#define Ne_OBJECT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "port.h"

/*
 * Forward declarations
*/

typedef struct _type_object NeTypeObject;

#pragma region "Object"
/*
 *
 *      Nebula Object 
 * 
*/

#define NeObject_HEAD   NeObject obj_base

#define NeObject_HEAD_INIT(type) \
	{1, type}

typedef struct _object
{
    Ne_size_t obj_refCount;
    NeTypeObject* obj_type;
} NeObject;

#define NeObject_CAST(op) ((NeObject*)(op))
#define NeObject_CAST_CONST(op) ((const NeObject*)(op))

/*
 *      Functions
*/

// Create a new object
NeObject* NeObject_New(NeTypeObject* type);
#define NeObject_NEW(type, typedef) (type*)NeObject_New(typedef)

NeObject* NeObject_NewRef(NeObject* obj);
#define NeObject_NEW_REF(obj) NeObject_NewRef(NeObject_CAST(obj))

void NeObject_IncRef(NeObject* obj);
#define NeObject_INC_REF(obj) NeObject_IncRef(NeObject_CAST(obj))

void NeObject_DecRef(NeObject* obj);
#define NeObject_DEC_REF(obj) NeObject_DecRef(NeObject_CAST(obj))

static inline void NeObject_SetType(NeObject* obj, NeTypeObject* type) { obj->obj_type = type; }
#define NeObject_SET_TYPE(obj, type) NeObject_SetType(NeObject_CAST(obj), type)

#pragma endregion

#pragma region "Nebula Variable-sized Object"

/*
 *
 *      Nebula Variable-sized Container Object
 * 
*/

#define NeVarObject_HEAD    NeVarObject obj_base

#define NeVarObject_HEAD_INIT(type, size) \
	{NeObject_HEAD_INIT(type), size}

typedef struct _var_object
{
    NeObject_HEAD;
    Ne_size_t obj_size;
} NeVarObject;

#define NeVarObject_CAST(op) ((NeVarObject*)(op))
#define NeVarObject_CAST_CONST(op) ((const NeVarObject*)(op))

static inline void NeVarObject_SetSize(NeVarObject* obj, Ne_size_t size) { obj->obj_size = size; }
#define NeVarObject_SET_SIZE(obj, size) NeVarObject_SetSize(NeVarObject_CAST(obj), size)

#pragma endregion

#pragma region Misc

#define NeObject_TYPE(obj)  (NeObject_CAST(obj)->obj_type)
#define NeObject_SIZE(obj)  (NeVarObject_CAST(obj)->obj_size)

#pragma endregion

#ifdef __cplusplus
}
#endif

#endif