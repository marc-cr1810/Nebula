#include "NeRuntime.h"

#include "Memory/Memory.h"

NeRuntimeState NeRuntime = { .initialized = 0, .coreInitialized = 0};

NeStatus NeRuntime_Init()
{
    if (NeRuntime.initialized)
        return NeStatus_Ok();

    NeRuntime.initialized = 1;
    return NeStatus_Ok();
}

void NeRuntime_Finalize()
{
    if (!NeRuntime.initialized)
        return;
    
    Mem_Free(NeRuntime.interpMain->thread);
    Mem_Free(NeRuntime.interpMain);

    NeRuntime.initialized = 0;
}


NeInterpreterState* NeRuntime_GetInterpreterState()
{
    return NeRuntime.interpMain;
}

NeThreadState* NeRuntime_GetThreadState()
{
    return NeRuntime.interpMain->thread;
}