#include "NeBaseObject.h"

#include "Memory/Memory.h"

static void BaseObject_Dealloc(NeObject* self)
{
    NeObject_TYPE(self)->typ_free(NeObject_CAST(self));
}

NeTypeObject NeBaseType = {
    NeVarObject_HEAD_INIT(&NeBaseType, 0),
    .typ_name = "type",
    .typ_doc = "Base type",
    .typ_size = sizeof(NeObject),
    .typ_itemSize = 0,
    .typ_dealloc = (destructor)BaseObject_Dealloc,
    .typ_base = NULL,
    .typ_free = Mem_Free
};