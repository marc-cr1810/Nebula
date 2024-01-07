#include "NeThread.h"

#include "Core/NeInterpreter.h"
#include "Memory/Memory.h"

NeThreadState* NeThreadState_New(struct _interpreter_state* interp)
{
    NeThreadState* thread = (NeThreadState*)Mem_Alloc(sizeof(NeThreadState));
    if (thread == NULL)
        return NULL;

    thread->interp = interp;
    interp->thread = thread;

    thread->currentException = NULL;

    return thread;
}