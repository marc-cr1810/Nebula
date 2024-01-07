#include "NeError.h"

#include "port.h"
#include "Memory/Memory.h"
#include "Core/NeThread.h"
#include "Objects/NeStringObject.h"

void NeError_Set(NeObject* exception)
{
    NeError_SetObject(exception, NeObject_CAST(NULL));
}

void NeError_SetObject(NeObject* exception, NeObject* value)
{
    if (!NeException_Check(exception))
    {
        NeError_SET_STRING(&NeSystemErrorException, "exception is not an Exception object");
        return;
    }
    assert(NeString_Check(value));

    NeExceptionObject* exc = NeException_SafeCast(exception);
    NeObject_INC_REF(value);
    exc->obj_context = value;
    NeError_RESTORE(exc);
}

void NeError_SetString(NeObject* exception, Ne_string_t str)
{
    NeObject* value = NeStringObject_FromCharArray(str);
    NeError_SetObject(exception, value);
    NeObject_DEC_REF(value);
}

void NeError_Clear()
{
    NeError_Restore(NULL);
}

void NeError_Restore(NeObject* exception)
{
    NeThreadState* thread = NeThreadState_Get();
    NeObject* oldException;

    oldException = thread->currentException;
    thread->currentException = exception;

    NeObject_INC_REF(exception);
    NeObject_DEC_REF(oldException);
}

void NeError_Format(NeObject* exception, Ne_string_t format, ...)
{
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Determine the size of the formatted string
    int size = vsnprintf(NULL, 0, format, args);

    // Allocate memory for the formatted string
    char* result = (char*)Mem_Alloc(size + 1);

    // Reset the argument list and format the string
    va_start(args, format);
    vsnprintf(result, size + 1, format, args);

    // Clean up and return the formatted string
    va_end(args);

    NeError_SetString(exception, result);
}

void NeError_Fatal(NeObject* exception, Ne_string_t msg)
{
    NeError_SET_STRING(exception, msg);
}

void NeError_FatalString(Ne_string_t msg)
{
    NeError_FATAL(&NeSystemErrorException, msg);
}

void NeError_Print()
{
    NeThreadState* thread = NeThreadState_Get();
    assert(thread != NULL);

    if (!NeError_Occured())
        return;
    
    NeExceptionObject* exc = NeException_SafeCast(thread->currentException);
    Ne_string_t name = exc->obj_typeStr;
    Ne_string_t context = NeString_SafeCast(exc->obj_context)->obj_value;

    printf("\n%s: %s", name, context);
}

NeObject* NeError_Occured()
{
    NeThreadState* thread = NeThreadState_Get();
    assert(thread != NULL);
    return thread->currentException;
}