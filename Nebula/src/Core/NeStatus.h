#ifndef Ne_NESTATUS_H
#define Ne_NESTATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _status
{    
	enum _type
	{
		NeStatus_TYPE_OK = 0,
		NeStatus_TYPE_ERROR = 1,
		NeStatus_TYPE_EXIT = 2
	} type;
	const char* func;
	const char* error_msg;
	int exit_code;
} NeStatus;

NeStatus NeStatus_Ok();
NeStatus NeStatus_Error(const char* error_msg);
NeStatus NeStatus_NoMemory();
NeStatus NeStatus_Exit(int exit_code);

int NeStatus_IsError(NeStatus status);
int NeStatus_IsExit(NeStatus status);
int NeStatus_Exception(NeStatus status);

#ifdef __cplusplus
}
#endif

#endif