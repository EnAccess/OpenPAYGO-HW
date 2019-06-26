#ifndef opaygo_decoder_h
#define opaygo_decoder_h

#include <stdio.h>
#include "opaygo_core.h"
#include "opaygo_value_utils.h"
#include "device_parameters.h"

#define MAX_TOKEN_JUMP 995

int GetActivationValueFromToken(uint32_t InputToken, int *LastCount);

#endif 
