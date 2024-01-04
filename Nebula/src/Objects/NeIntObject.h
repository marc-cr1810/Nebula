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

/*
 *  API Macros
*/

#define NeInt_Check(self) NeTypeObject_TypeCheck(self, &NeIntType)
#define NeInt_CheckExact(self) NeTypeObject_IS_TYPE(self, &NeIntType)

#define NeInt_Cast(obj) ((NeIntObject*)obj)
#define NeInt_SafeCast(obj) (assert(NeInt_Check(obj)), NeInt_Cast(obj))

/*
 *  Methods
*/

NeAPI_FUNC(NeObject*) NeIntObject_FromInt(Ne_int32_t value);

#ifdef __cplusplus
}
#endif

#endif