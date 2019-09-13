#ifndef opaygo_decoder_h
#define opaygo_decoder_h

#include <stdio.h>
#include "opaygo_core.h"
#include "opaygo_value_utils.h"
#include "restricted_digit_set_mode.h"

#define MAX_TOKEN_JUMP 30
#define MAX_TOKEN_JUMP_COUNTER_SYNC 100

int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]);

#endif 
