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

    int neRecursionRemaining;
    int neRecursionLimit;
    int cRecursionRemaining;
    int cRecursionHeadroom;
} NeThreadState;

NeAPI_FUNC(NeThreadState*) NeThreadState_New(struct _interpreter_state* interp);

NeAPI_FUNC(NeThreadState*) NeThreadState_Get();

static inline int NeThreadState_MakeRecursiveCheck(NeThreadState* thread) { return thread->cRecursionRemaining-- <= 0; }
int NeThreadState_CheckRecursiveCall(NeThreadState* thread, Ne_string_t where);

static inline int NeThreadState_EnterRecursiveCall(NeThreadState* thread, Ne_string_t where) 
{ 
    return NeThreadState_MakeRecursiveCheck(thread) && NeThreadState_CheckRecursiveCall(thread, where); 
}
static inline int NeThreadState_LeaveRecursiveCall(NeThreadState* thread) { return thread->cRecursionRemaining++; }

#ifdef __cplusplus
}
#endif

#endif