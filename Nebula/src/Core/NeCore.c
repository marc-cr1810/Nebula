#include "NeCore.h"

#include "Nebula.h"

static NeTypeObject* s_StaticTypes[] =
{
    &NeBaseType,

    &NeIntType,
    &NeStringType
};

static NeStatus InitTypes()
{
	for (Ne_size_t i = 0; i < Ne_Array_Length(s_StaticTypes); i++) {
		NeTypeObject* type = s_StaticTypes[i];
        if (NeTypeObject_Ready(type) < 0)
            return NeStatus_Error("Failed to initialize built-in type!");
    }

    return NeStatus_Ok();
}

NeStatus NeCore_Init()
{
    NeStatus status = InitTypes();
    if (NeStatus_IsError(status))
        return status;

    return NeStatus_Ok();
}

NeStatus NeCore_Finalize()
{
    return NeStatus_Ok();
}