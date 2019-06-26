#ifndef opaygo_value_utils_h
#define opaygo_value_utils_h

#include <stdio.h>

int DecodeBase(int StartingCodeBase, int TokenBase);
int GetTokenBase(uint32_t Token);
uint32_t PutBaseInToken(uint32_t Token, int TokenBase);

#endif
