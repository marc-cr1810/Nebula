#include "NeExceptionObject.h"

#define NE_EXCEPTION_TYPE_DEF(type, name, desc)         \
NeTypeObject Ne ## type ## Type =                       \
{                                                       \
    NeVarObject_HEAD_INIT(&Ne ## type ## Type, 0),      \
    .typ_name = name,                                   \
    .typ_doc = desc,                                    \
    .typ_size = sizeof(NeExceptionObject),              \
    .typ_itemSize = 0,                                  \
    .typ_flags = TPFLAGS_DEFAULT | TPFLAGS_BASETYPE     \
    | TPFLAGS_BASE_EXC_SUBCLASS,                        \
    .typ_dealloc = NULL,                                \
    .typ_base = &NeExceptionType,                       \
    .typ_free = NULL                                    \
};


#define NE_EXCEPTION_VALUE_DEF(type, name, exitCode)	\
NeExceptionObject Ne ## type = {						\
	NeVarObject_HEAD_INIT(&Ne ## type ## Type, 0),		\
	name,					                            \
	NULL,												\
	exitCode,											\
};


#define NE_EXCEPTION_DEF(type, name, desc, exitCode)	\
NE_EXCEPTION_TYPE_DEF(type, name, desc);				\
NE_EXCEPTION_VALUE_DEF(type, name, exitCode)

NeTypeObject NeExceptionType =
{
    NeVarObject_HEAD_INIT(&NeExceptionType, 0),
    .typ_name = "Exception",
    .typ_doc = "Exception object type",
    .typ_size = sizeof(NeExceptionObject),
    .typ_itemSize = 0,
    .typ_flags = TPFLAGS_DEFAULT | TPFLAGS_BASETYPE 
    | TPFLAGS_BASE_EXC_SUBCLASS,
    .typ_dealloc = NULL,
    .typ_base = NULL,
    .typ_free = NULL
};


NE_EXCEPTION_VALUE_DEF(Exception, "Exception", EXC_EXIT_EXCEPTION);

NE_EXCEPTION_DEF(TypeErrorException, "TypeErrorException", "Type error exception object type", EXC_EXIT_TYPE_ERROR);
NE_EXCEPTION_DEF(IndexErrorException, "IndexErrorException", "Index error exception object type", EXC_EXIT_INDEX_ERROR);
NE_EXCEPTION_DEF(ValueErrorException, "ValueErrorException", "Value error exception object type", EXC_EXIT_VALUE_ERROR);

NE_EXCEPTION_DEF(SyntaxErrorException, "SyntaxErrorException", "Syntax error exception object type", EXC_EXIT_SYNTAX_ERROR);
NE_EXCEPTION_DEF(IndentationErrorException, "IndentationErrorException", "Indentation error exception object type", EXC_EXIT_INDENTATION_ERROR);
NE_EXCEPTION_DEF(RecursionErrorException, "RecursionErrorException", "Recursion error exception object type", EXC_EXIT_RECURSION_ERROR);

NE_EXCEPTION_DEF(SystemErrorException, "SystemErrorException", "System error exception object type", EXC_EXIT_SYSTEM_ERROR);
NE_EXCEPTION_DEF(RuntimeErrorException, "RuntimeErrorException", "Runtime error exception object type", EXC_EXIT_RUNTIME_ERROR);
NE_EXCEPTION_DEF(MemoryErrorException, "MemoryErrorException", "Memory error exception object type", EXC_EXIT_MEMORY_ERROR);