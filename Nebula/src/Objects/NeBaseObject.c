#include "NeBaseObject.h"

#include "Error/NeError.h"
#include "Memory/Memory.h"

#include "Objects/NeStringObject.h"

static NeObject* BaseObject_StrRepr(NeObject* self)
{
    NeObject* str = NeStringObject_FromCharArray(NeObject_TYPE(self)->typ_name);
    return str;
}

static Ne_hash_t BaseObject_Hash(NeObject* self)
{
    NeError_FORMAT(&NeTypeErrorException, "unhashable type '%.200s'", NeObject_TYPE(self)->typ_name);
    return -1;
}

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
    .typ_strRepr = (strRepr)BaseObject_StrRepr,
    .typ_hash = (hashFunc)BaseObject_Hash,
    .typ_dealloc = (destructor)BaseObject_Dealloc,
    .typ_base = NULL,
    .typ_free = Mem_Free
};