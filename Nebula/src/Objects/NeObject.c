#include "NeObject.h"

#include "Memory/Memory.h"
#include "Core/NeThread.h"
#include "Error/NeError.h"
#include "Objects/NeTypeObject.h"
#include "Objects/NeStringObject.h"

static inline void ObjectSetType(NeObject* obj, NeTypeObject* type)
{
    obj->obj_type = type;
}

static inline void ObjectNewRef(NeObject* obj)
{
    obj->obj_refCount = 1;
}

static inline void ObjectInit(NeObject* obj, NeTypeObject* type)
{
    ObjectSetType(obj, type);
    ObjectNewRef(obj);
}

NeObject* NeObject_New(NeTypeObject* type)
{
    NeObject* obj = Mem_Alloc(type->typ_size);
    ObjectInit(obj, type);
    return obj;
}

NeObject* NeObject_NewRef(NeObject* obj)
{
    if (obj)
        NeObject_IncRef(obj);
    return obj;
}

void NeObject_IncRef(NeObject* obj)
{
    if (obj)
        obj->obj_refCount++;
}

void NeObject_DecRef(NeObject* obj)
{
    if (obj)
    {
        obj->obj_refCount--;
        if (obj->obj_refCount <= 0)
            NeObject_TYPE(obj)->typ_dealloc(obj);
    }
}

NeObject* NeObject_ToString(NeObject* obj)
{
    if (!NeObject_TYPE(obj)->typ_strRepr)
        return NeStringObject_FromFormat("<%s object at %p>", NeObject_TYPE(obj)->typ_name, obj);

    NeThreadState* thread = NeThreadState_Get();
    if (NeThreadState_EnterRecursiveCall(thread, "while getting the string representation of an object"))
        return NULL;
    NeObject* repr = NeObject_TYPE(obj)->typ_strRepr(obj);
    NeThreadState_LeaveRecursiveCall(thread);

    if (!repr)
        goto error;
    
    if (!NeString_Check(repr))
    {
        NeError_FORMAT(&NeTypeErrorException, "returned a non-string (type %.200s)", NeObject_TYPE(obj)->typ_name);
        NeObject_DEC_REF(repr);
        return NULL;
    }

    return repr;

error:
    return NeStringObject_FromCharArray("<NULL>");
}

void NeObject_Print(NeObject* obj)
{
    NeStringObject* str = NeString_SafeCast(NeObject_TO_STRING(obj));
    printf(str->obj_value);
}

Ne_hash_t NeObject_Hash(NeObject* obj)
{
    return NeObject_TYPE(obj)->typ_hash(obj);
}