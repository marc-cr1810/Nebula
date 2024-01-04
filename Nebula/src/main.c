#include "Nebula.h"

int NeMain_Run(int argc, char *argv[])
{
  NeStatus status = NeCore_Init();
  if (NeStatus_IsError(status))
  {
    printf("Error: %s", status.error_msg);
    return status.exit_code;
  }

  NeObject* str = NeStringObject_FromFormat("Hello world! %i", 10);
  printf(NeString_Cast(str)->obj_value);

  status = NeCore_Finalize();
  if (NeStatus_IsError(status))
    printf("Error: %s", status.error_msg);

  return status.exit_code;
}

int main(int argc, char *argv[])
{
  return NeMain_Run(argc, argv);
}
