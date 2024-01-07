#ifndef Ne_RUNTIME_H
#define Ne_RUNTIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Core/NeStatus.h"
#include "Core/NeInterpreter.h"

typedef struct _runtime_state
{
    int initialized;
    int coreInitialized;

    NeInterpreterState* interpMain;
} NeRuntimeState;

extern NeRuntimeState NeRuntime;

/*
 *  Methods
*/

NeAPI_FUNC(NeStatus) NeRuntime_Init();
NeAPI_FUNC(void) NeRuntime_Finalize();

NeAPI_FUNC(NeInterpreterState*) NeRuntime_GetInterpreterState();
NeAPI_FUNC(NeThreadState*) NeRuntime_GetThreadState();

#ifdef __cplusplus
}
#endif

#endif