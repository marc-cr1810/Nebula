#include "NeTypeObject.h"

#include "Objects/NeBaseObject.h"

static int ReadyPreChecks(NeTypeObject* type)
{
    if (type->typ_flags & TPFLAGS_READY)
        return 1;

    assert((type->typ_flags & TPFLAGS_READYING) == 0);

    type->typ_flags |= TPFLAGS_READYING;

    if (type->typ_name == NULL)
    {
        // TODO: Return error
        return -1;
    }

    return 0;
}

static int ReadyBaseType(NeTypeObject* type)
{
    NeTypeObject* base;

    // Initialize the base typ_base (defaults to NeBaseType unless that is us)
    base = type->typ_base;
    if (base == NULL && type != &NeBaseType)
    {
        base = &NeBaseType;
        if (type->typ_flags & TPFLAGS_HEAPTYPE)
            type->typ_base = (NeTypeObject*)NeObject_NEW_REF(base);
        else
            type->typ_base = base;
    }

    if (base != NULL)
    {
        if (NeTypeObject_Ready(base) < 0)
            return -1;
    }

    if (NeTypeObject_IS_TYPE(type, NULL) && base != NULL)
        NeObject_SET_TYPE(type, NeObject_TYPE(base));

        return 0;
}

static int ReadyInherit(NeTypeObject* type)
{
    if (NeTypeObject_IS_TYPE(type, &NeBaseType))
        return 0;

    NeTypeObject* base = type->typ_base;

    if (base == NULL)
        return -1;

    if (type->typ_strRepr == NULL)
        type->typ_strRepr = base->typ_strRepr;

    if (type->typ_hash == NULL)
        type->typ_hash = base->typ_hash;

    if (type->typ_dealloc == NULL)
        type->typ_dealloc = base->typ_dealloc;

    if (type->typ_free == NULL)
        type->typ_free = base->typ_free;

    return 0;
}

static void ReadyStopReadying(NeTypeObject* type)
{
    type->typ_flags &= ~TPFLAGS_READYING;
    type->typ_flags |= TPFLAGS_READY;
}

int NeTypeObject_Ready(NeTypeObject* type)
{
    int check = ReadyPreChecks(type);
    if (check < 0)
        goto error;
    else if (check > 0)
        return 0;

    if (ReadyBaseType(type) < 0)
        goto error;
    if (ReadyInherit(type) < 0)
        goto error;

    ReadyStopReadying(type);
    return 0;

    error:
    ReadyStopReadying(type);
    return -1;
}

int NeTypeObject_IsSubtype(const NeTypeObject* a, const NeTypeObject* b)
{
    do
    {
        if (a == b)
            return 1;
        a = a->typ_base;
    } while (a != NULL);
    return (b == &NeBaseType);
}