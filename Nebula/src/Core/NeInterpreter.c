#include "NeInterpreter.h"

#include "Core/NeRuntime.h"
#include "Memory/Memory.h"

NeInterpreterState* NeInterpreterState_New()
{
    NeInterpreterState* interp = (NeInterpreterState*)Mem_Alloc(sizeof(NeInterpreterState));
    if (interp == NULL)
        return NULL;

    NeRuntimeState* runtime = &NeRuntime;
    interp->runtime = runtime;

    runtime->interpMain = interp;

    return interp;
}