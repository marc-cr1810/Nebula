#include "NeCore.h"

#include "Nebula.h"

static NeTypeObject* s_StaticTypes[] =
{
    &NeBaseType,

    &NeIntType,
    &NeStringType,

    // Exception types
    &NeExceptionType,
	
	&NeTypeErrorExceptionType,
	&NeIndexErrorExceptionType,
	&NeValueErrorExceptionType,
	&NeSyntaxErrorExceptionType,
	&NeIndentationErrorExceptionType,
	&NeSystemErrorExceptionType,
	&NeRuntimeErrorExceptionType,
	&NeMemoryErrorExceptionType
};

static NeStatus InitTypes()
{
	for (Ne_size_t i = 0; i < Ne_Array_Length(s_StaticTypes); i++) {
		NeTypeObject* type = s_StaticTypes[i];
        if (NeTypeObject_Ready(type) < 0)
            return NeStatus_Error("Failed to initialize built-in type!");
    }

    return NeStatus_Ok();
}

static NeStatus CreateInterpreter(NeRuntimeState* runtime)
{
    NeInterpreterState* interp = NeInterpreterState_New();
    if (interp == NULL)
        return NeStatus_Error("failed to initialize the interpreter!");

    NeThreadState* thread = NeThreadState_New(interp);
    if (thread == NULL)
        return NeStatus_Error("failed to make the first thread!");

    return NeStatus_Ok();
}

NeStatus NeCore_Init()
{
    NeStatus status = NeRuntime_Init();
    if (NeStatus_IsError(status))
        return status;

    NeRuntimeState* runtime = &NeRuntime;
    if (!runtime->coreInitialized)
    {
        status = InitTypes();
        if (NeStatus_IsError(status))
            return status;

        status = CreateInterpreter(runtime);
        if (NeStatus_IsError(status))
            return status;

        runtime->coreInitialized = 1;
    }

    return NeStatus_Ok();
}

NeStatus NeCore_Finalize()
{
    NeRuntime_Finalize();

    return NeStatus_Ok();
}