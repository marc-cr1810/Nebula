#ifndef Ne_NECORE_H
#define Ne_NECORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Core/NeStatus.h"

NeStatus NeCore_Init();
NeStatus NeCore_Finalize();

#ifdef __cplusplus
}
#endif

#endif