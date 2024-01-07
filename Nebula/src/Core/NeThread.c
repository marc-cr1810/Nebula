#include "NeThread.h"

#include "Core/NeInterpreter.h"
#include "Core/NeRuntime.h"
#include "Error/NeError.h"
#include "Memory/Memory.h"

NeThreadState* NeThreadState_New(struct _interpreter_state* interp)
{
    NeThreadState* thread = (NeThreadState*)Mem_Alloc(sizeof(NeThreadState));
    if (thread == NULL)
        return NULL;

    thread->interp = interp;
    interp->thread = thread;

    thread->currentException = NULL;

    thread->neRecursionLimit = NE_RECURSION_LIMIT;
    thread->neRecursionRemaining = NE_RECURSION_LIMIT;
    thread->cRecursionRemaining = C_RECURSION_LIMIT;
    thread->cRecursionHeadroom = 50;

    return thread;
}

NeThreadState* NeThreadState_Get()
{
    return NeRuntime_GetThreadState();
}

int NeThreadState_CheckRecursiveCall(NeThreadState* thread, Ne_string_t where)
{
    if (thread->cRecursionHeadroom)
    {
        if (thread->cRecursionRemaining < -thread->cRecursionHeadroom)
            NeError_FATALSTRING("Cannot recover from stack overflow");
    }
    else
    {
        if (thread->cRecursionRemaining <= 0)
        {
            NeError_FORMAT(&NeRecursionErrorException, "maximum recursion depth exceeded %s", where);
            ++thread->cRecursionRemaining;
            return 0;
        }
    }
    return 1;
}