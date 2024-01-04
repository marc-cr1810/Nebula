#include "Nebula.h"

int NeMain_Run(int argc, char *argv[])
{
  NeStatus status = NeCore_Init();
  if (NeStatus_IsError(status))
  {
    printf("Error: %s", status.error_msg);
    return status.exit_code;
  }

  NeObject* obj = NeIntObject_FromInt(10);
  printf("%i", ((NeIntObject*)obj)->obj_value);

  status = NeCore_Finalize();
  if (NeStatus_IsError(status))
    printf("Error: %s", status.error_msg);

  return status.exit_code;
}

int main(int argc, char *argv[])
{
  return NeMain_Run(argc, argv);
}
