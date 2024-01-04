#ifndef Ne_INTOBJECT_H
#define Ne_INTOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Objects/NeTypeObject.h"

typedef struct _int_object
{
    NeVarObject_HEAD;
    Ne_int32_t obj_value;
} NeIntObject;

NeAPI_DATA(NeTypeObject) NeIntType;

NeAPI_FUNC(NeObject*) NeIntObject_FromInt(Ne_int32_t value);

#ifdef __cplusplus
}
#endif

#endif