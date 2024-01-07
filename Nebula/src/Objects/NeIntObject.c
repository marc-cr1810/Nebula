#include "NeIntObject.h"

#include "Memory/Memory.h"
#include "Objects/NeStringObject.h"

NeObject* IntObject_StrRepr(NeObject* self)
{
    int value = NeInt_SafeCast(self)->obj_value;
    int maxDigits = snprintf(NULL, 0, "%d", value);

    char strValue[maxDigits + 1];
    sprintf(strValue, "%d", value);

    return NeStringObject_FromCharArray((const char*)strValue);
}

NeTypeObject NeIntType = {
    NeVarObject_HEAD_INIT(&NeIntType, 0),
    .typ_name = "int",
    .typ_doc = "An integer object",
    .typ_size = sizeof(NeIntObject),
    .typ_flags = TPFLAGS_DEFAULT | TPFLAGS_BASETYPE,
    .typ_strRepr = IntObject_StrRepr,
    .typ_hash = NULL,
    .typ_dealloc = NULL,
    .typ_base = NULL,
    .typ_free = NULL
};

/*
 * Api Functions
*/

NeObject* NeIntObject_FromInt(Ne_int32_t value)
{
    NeIntObject* obj = NeObject_NEW(NeIntObject, &NeIntType);
    obj->obj_value = value;
    return NeObject_CAST(obj);
}