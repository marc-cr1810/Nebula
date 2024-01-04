#include "NeObject.h"

#include "Memory/Memory.h"
#include "Objects/NeTypeObject.h"

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