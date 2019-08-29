#ifndef opaygo_core_h
#define opaygo_core_h

#include <stdio.h>

#define MAX_ACTIVATION_VALUE 995
#define PAYG_DISABLE_VALUE 998
#define COUNTER_SYNC_VALUE 999

uint32_t GenerateOPAYGOToken(uint32_t LastToken);

#endif
