#include "NeStringObject.h"

#include "Memory/Memory.h"

NeTypeObject NeStringType = {
    NeVarObject_HEAD_INIT(&NeStringType, 0),
    .typ_name = "string",
    .typ_doc = "String object type",
    .typ_size = sizeof(NeStringObject),
    .typ_itemSize = 0,
    .typ_flags = TPFLAGS_DEFAULT | TPFLAGS_BASETYPE,
    .typ_dealloc = NULL,
    .typ_base = NULL,
    .typ_free = NULL
};

NeObject* NeStringObject_FromCharArray(Ne_string_t str)
{
    return NeStringObject_FromCharArrayAndSize(str, strlen(str));
}

NeObject* NeStringObject_FromCharArrayAndSize(Ne_string_t str, Ne_size_t size)
{
    NeStringObject* obj;
    Ne_size_t alloc;

    if (size < 0)
    {
        // TODO: Print error
        return NULL;
    }

    obj = NeObject_NEW(NeStringObject, &NeStringType);
    if (obj == NULL)
        return NULL;
    if (size == 0)
    {
        obj->obj_value = NULL;
        alloc = 0;
    }
    else
    {
        alloc = size + 1;
        obj->obj_value = (char*)Mem_Alloc(alloc);
        if (str != NULL && size > 0)
            memcpy(obj->obj_value, str, size);
        obj->obj_value[size] = '\0'; // Tailing NULL byte (end of string)
    }

    NeVarObject_SET_SIZE(obj, size);
    obj->obj_alloc = alloc;
    return NeObject_CAST(obj);
}

NeObject* NeStringObject_FromFormat(Ne_string_t format, ...)
{
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Determine the size of the formatted string
    int size = vsnprintf(NULL, 0, format, args);

    // Allocate memory for the formatted string
    char* result = (char*)Mem_Alloc(size + 1);

    // Reset the argument list and format the string
    va_start(args, format);
    vsnprintf(result, size + 1, format, args);

    // Clean up and return the formatted string
    va_end(args);
    return NeStringObject_FromCharArray(result);
}

NeObject* NeStringObject_ConcatString(NeObject* a, Ne_string_t b)
{
    NeObject* bStr = NeStringObject_FromCharArray(b);
    NeObject* result = NeStringObject_Concat(a, bStr);
    NeObject_DEC_REF(bStr);
    return result;
}

NeObject* NeStringObject_Concat(NeObject* a, NeObject* b)
{
    if (!NeString_Check(a) || !NeString_Check(b))
    {
        // TODO: report error
        return NULL;
    }

    NeStringObject* result = NULL;

    if (NeObject_SIZE(a) == 0)
    {
        result = NeString_SafeCast(b);
        NeObject_INC_REF(result);
        return NeObject_CAST(result);
    }

    if (NeObject_SIZE(b) == 0)
    {
        result = NeString_SafeCast(a);
        NeObject_INC_REF(result);
        return NeObject_CAST(result);
    }

    result = NeString_SafeCast(NeStringObject_FromCharArrayAndSize(NULL, NeObject_SIZE(a) + NeObject_SIZE(b)));
    if (result)
    {
        memcpy(result->obj_value, NeString_SafeCast(a)->obj_value, NeObject_SIZE(a));
        memcpy(result->obj_value + NeObject_SIZE(a), NeString_SafeCast(b)->obj_value, NeObject_SIZE(b));
    }

    return NeObject_CAST(result);
}