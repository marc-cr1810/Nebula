#ifndef Ne_ERROR_H
#define Ne_ERROR_H

#include "port.h"
#include "Objects/NeExceptionObject.h"

#ifdef __cplusplus
extern "C" {
#endif

void NeError_Set(NeObject* exception);
void NeError_SetObject(NeObject* exception, NeObject* value);
void NeError_SetString(NeObject* exception, Ne_string_t str);

void NeError_Clear();
void NeError_Restore();

void NeError_Format(NeObject* exception, Ne_string_t format, ...);

void NeError_Fatal(NeObject* exception, Ne_string_t msg);
void NeError_FatalString(Ne_string_t msg);

void NeError_Print();
NeObject* NeError_Occured();

/*
 *  API Macros
*/

#define NeError_SET(exception) NeError_Set(NeObject_CAST(exception))
#define NeError_SET_OBJECT(exception, value) NeError_SetObject(NeObject_CAST(exception), value)
#define NeError_SET_STRING(exception, value) NeError_SetString(NeObject_CAST(exception), value)

#define NeError_CLEAR() NeError_Clear()
#define NeError_RESTORE() NeError_Restore()

#define NeError_FORMAT(exception, format, ...) NeError_Format(NeError_CAST(exception), format, __VA_ARGS__)

#define NeError_FATAL(exception, msg) NeError_Fatal(NeObject_CAST(exception), msg)
#define NeError_FATALSTRING(msg) NeError_Fatal(msg)

#define NeError_PRINT()

// Helper macros

#define NeError_OUT_OF_MEMORY() NeError_SET_STRING(&NeMemoryErrorException, "out of memory")

#ifdef __cplusplus
}
#endif

#endif