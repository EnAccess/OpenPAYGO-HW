//
//  opaygo_core_extended.c
//  OPAYGO-Unix
//
//  Created by Benjamin David on 17/09/2019.
//  Copyright © 2019 Solaris Offgrid. All rights reserved.
//

#ifndef OPAYGO_DECODER_H
#define OPAYGO_DECODER_H

#include <stdint.h>

#define MAX_TOKEN_JUMP 30
#define MAX_TOKEN_JUMP_COUNTER_SYNC 100

#define MAX_ACTIVATION_VALUE 995
#define PAYG_DISABLE_VALUE 998
#define COUNTER_SYNC_VALUE 999

int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]);

int DecodeBase(int StartingCodeBase, int TokenBase);
int GetTokenBase(uint32_t Token);
uint32_t PutBaseInToken(uint32_t Token, int TokenBase);
uint32_t GenerateOPAYGOToken(uint32_t LastToken, char SECRET_KEY[16]);

uint32_t ConvertFromFourDigitToken(uint64_t FourDigitToken);

// functions for extended token
int32_t GetActivationValueFromExtendedToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]);
uint64_t GenerateOPAYGOTokenExtended(uint64_t LastToken, char SECRET_KEY[16]);
uint32_t DecodeBaseExtended(uint32_t StartingCodeBase, uint32_t TokenBase);
uint32_t GetTokenBaseExtended(uint64_t Token);
uint64_t PutBaseInTokenExtended(uint64_t Token, uint32_t TokenBase);

#endif
