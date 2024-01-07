#ifndef Ne_EXCEPTIONOBJECT_H
#define Ne_EXCEPTIONOBJECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Objects/NeTypeObject.h"

#define NE_EXCEPTION_OBJ_TYPE_DEF(type) \
NeAPI_DATA(NeExceptionObject) Ne ## type; \
NeAPI_DATA(NeTypeObject) Ne ## type ## Type;

/*
 * Exception code definitions
*/

#define EXC_EXIT_EXCEPTION          1
#define EXC_EXIT_TYPE_ERROR         2
#define EXC_EXIT_INDEX_ERROR        3
#define EXC_EXIT_VALUE_ERROR        4
#define EXC_EXIT_SYNTAX_ERROR       5
#define EXC_EXIT_INDENTATION_ERROR  6
#define EXC_EXIT_RECURSION_ERROR    7
#define EXC_EXIT_SYSTEM_ERROR       8
#define EXC_EXIT_RUNTIME_ERROR      9
#define EXC_EXIT_MEMORY_ERROR       10

typedef struct _exception_object
{
    NeVarObject_HEAD;
    Ne_string_t obj_typeStr;
    NeObject* obj_context;
    Ne_int32_t obj_exitCode;
} NeExceptionObject;

/*
 *  API Macros
*/

#define NeException_Check(self) ((NeObject_TYPE(self)->typ_flags & TPFLAGS_BASE_EXC_SUBCLASS) != 0)

#define NeException_Cast(obj) ((NeExceptionObject*)obj)
#define NeException_SafeCast(obj) (assert(NeException_Check(obj)), NeException_Cast(obj))

/*
*		Exception Definitions
*/

NE_EXCEPTION_OBJ_TYPE_DEF(Exception);

NE_EXCEPTION_OBJ_TYPE_DEF(TypeErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(IndexErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(ValueErrorException);

NE_EXCEPTION_OBJ_TYPE_DEF(SyntaxErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(IndentationErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(RecursionErrorException);

NE_EXCEPTION_OBJ_TYPE_DEF(SystemErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(RuntimeErrorException);
NE_EXCEPTION_OBJ_TYPE_DEF(MemoryErrorException);

#ifdef __cplusplus
}
#endif

#endif