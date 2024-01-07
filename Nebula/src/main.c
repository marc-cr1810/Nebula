#include "Nebula.h"

int NeMain_Run(int argc, char *argv[])
{
  NeStatus status = NeCore_Init();
  if (NeStatus_IsError(status))
  {
    printf("Error: %s", status.error_msg);
    return status.exit_code;
  }

  NeObject* intObj = NeIntObject_FromInt(420);
  NeObject* str = NeStringObject_FromCharArray("Hello world! ");
  str = NeStringObject_Concat(str, NeObject_TO_STRING(intObj));
  NeObject_PRINT(str);

  status = NeCore_Finalize();
  if (NeStatus_IsError(status))
    printf("Error: %s", status.error_msg);

  return status.exit_code;
}

int main(int argc, char *argv[])
{
  return NeMain_Run(argc, argv);
}
