#include "opaygo_decoder.h"


int GetActivationValueFromToken(uint64_t InputToken, int *LastCount) {
    
#ifdef RESTRICTED_DIGIT_SET_MODE
    InputToken = ConvertFromFourDigitToken(InputToken);
#endif
    
    int StartingCodeBase = GetTokenBase(StartingCode);
    int TokenBase = GetTokenBase(InputToken);
    uint32_t CurrentToken = PutBaseInToken(StartingCode, TokenBase);
    uint32_t MaskedToken;
    int MaxCountTry;
    
    int Value = DecodeBase(StartingCodeBase, TokenBase);
    
    if(Value == COUNTER_SYNC_VALUE) {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP_COUNTER_SYNC;
    } else {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP;
    }
    
    for (int Count=0; Count <= MaxCountTry; Count++) {
        MaskedToken = PutBaseInToken(CurrentToken, TokenBase);
        if(MaskedToken == InputToken && Count > *LastCount) {
            *LastCount = Count;
            return Value;
        }
        CurrentToken = GenerateOPAYGOToken(CurrentToken);
    }
    
    return -1;
}
