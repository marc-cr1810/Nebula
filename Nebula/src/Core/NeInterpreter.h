#ifndef Ne_INTERPRETER_H
#define Ne_INTERPRETER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "port.h"
#include "Core/NeThread.h"

struct _runtime_state;

typedef struct _interpreter_state
{
    struct _runtime_state* runtime;

    NeThreadState* thread;
} NeInterpreterState;

NeAPI_FUNC(NeInterpreterState*) NeInterpreterState_New();

#ifdef __cplusplus
}
#endif

#endif