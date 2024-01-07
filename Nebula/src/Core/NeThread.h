#ifndef Ne_THREAD_H
#define Ne_THREAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Objects/NeObject.h"

struct _interpreter_state;

typedef struct _thread_state
{
    struct _interpreter_state* interp;

    NeObject* currentException;
} NeThreadState;

NeAPI_FUNC(NeThreadState*) NeThreadState_New(struct _interpreter_state* interp);

#ifdef __cplusplus
}
#endif

#endif