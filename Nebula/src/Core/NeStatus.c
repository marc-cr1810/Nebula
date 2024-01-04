#include "NeStatus.h"

#include "port.h"

#ifdef _MSC_VER
#  define NeStatus_GET_FUNC() __FUNCTION__
#else
#  define NeStatus_GET_FUNC() __func__
#endif

#define NeStatus_OK() { NeStatus_TYPE_OK, }

#define NeStatus_ERROR(ERROR_MSG) \
	{ \
		NeStatus_TYPE_ERROR, \
		NeStatus_GET_FUNC(), \
		(ERROR_MSG), \
	}

#define NeStatus_NO_MEMORY() NeStatus_ERROR("memory allocation failed")

#define NeStatus_EXIT(EXIT_CODE) \
	{ \
		NeStatus_TYPE_EXIT, \
		"", \
		"", \
		(EXIT_CODE) \
	}

#define NeStatus_IS_ERROR(status) (status.type == NeStatus_TYPE_ERROR)
#define NeStatus_IS_EXIT(status) (status.type == NeStatus_TYPE_EXIT)
#define NeStatus_EXCEPTION(status) (status.type != NeStatus_TYPE_OK)


NeStatus NeStatus_Ok()
{
	NeStatus status = NeStatus_OK();
	return status;
}

NeStatus NeStatus_Error(const char* error_msg)
{
	assert(error_msg != NULL);
	NeStatus status = NeStatus_ERROR(error_msg);
	return status;
}

NeStatus NeStatus_NoMemory()
{
	return NeStatus_Error("memory allocation failed");
}

NeStatus NeStatus_Exit(int exit_code)
{
	NeStatus status = NeStatus_EXIT(exit_code);
	return status;
}

int NeStatus_IsError(NeStatus status)
{
	return NeStatus_IS_ERROR(status);
}

int NeStatus_IsExit(NeStatus status)
{
	return NeStatus_IS_EXIT(status);
}

int NeStatus_Exception(NeStatus status)
{
	return NeStatus_EXCEPTION(status);
}
