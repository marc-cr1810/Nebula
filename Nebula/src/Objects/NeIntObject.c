#include "NeIntObject.h"

#include "Memory/Memory.h"


/*
 * Methods
*/

static void IntDealloc(NeIntObject* self)
{
	NeObject_TYPE(self)->typ_free((NeObject*)self);
}

NeTypeObject NeIntType = {
    NeVarObject_HEAD_INIT(&NeIntType, 0),
    .typ_name = "int",
    .typ_doc = "An integer object",
    .typ_size = sizeof(NeIntObject),
    .typ_flags = TPFLAGS_DEFAULT | TPFLAGS_BASETYPE,
    .typ_dealloc = (destructor)IntDealloc,
    .typ_base = NULL,
    .typ_free = Mem_Free
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