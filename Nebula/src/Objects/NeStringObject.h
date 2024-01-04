#ifndef Ne_STRINGOBJECT_H
#define Ne_STRINGOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "port.h"
#include "Objects/NeTypeObject.h"

typedef struct _string_object
{
    NeVarObject_HEAD;
    Ne_size_t obj_alloc;
    char* obj_value;
} NeStringObject;

NeAPI_DATA(NeTypeObject) NeStringType;

/*
 *  API Macros
*/

#define NeString_Check(self) NeTypeObject_TypeCheck(self, &NeStringType)
#define NeString_CheckExact(self) NeTypeObject_IS_TYPE(self, &NeStringType)

#define NeString_Cast(obj) ((NeStringObject*)obj)
#define NeString_SafeCast(obj) (assert(NeString_Check(obj)), NeString_Cast(obj))

/*
 *  Methods
*/

NeAPI_FUNC(NeObject*) NeStringObject_FromCharArray(Ne_string_t str);
NeAPI_FUNC(NeObject*) NeStringObject_FromCharArrayAndSize(Ne_string_t str, Ne_size_t size);

NeAPI_FUNC(NeObject*) NeStringObject_FromFormat(Ne_string_t format, ...);

NeAPI_FUNC(NeObject*) NeStringObject_ConcatString(NeObject* a, Ne_string_t b);
NeAPI_FUNC(NeObject*) NeStringObject_Concat(NeObject* a, NeObject* b);

#ifdef __cplusplus
}
#endif

#endif