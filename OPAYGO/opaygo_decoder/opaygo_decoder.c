#include "opaygo_decoder.h"


int GetActivationValueFromToken(uint32_t InputToken, int *LastCount) {
    int StartingCodeBase = GetTokenBase(StartingCode);
    int TokenBase = GetTokenBase(InputToken);
    uint32_t CurrentToken = PutBaseInToken(StartingCode, TokenBase);
    uint32_t MaskedToken;
    
    for (int Count=0; Count <= (*LastCount + MAX_TOKEN_JUMP); Count++) {
        MaskedToken = PutBaseInToken(CurrentToken, TokenBase);
        if(MaskedToken == InputToken && Count > *LastCount) {
            *LastCount = Count;
            return DecodeBase(StartingCodeBase, TokenBase);
        }
        CurrentToken = GenerateOPAYGOToken(CurrentToken);
    }
    
    return -1;
}
