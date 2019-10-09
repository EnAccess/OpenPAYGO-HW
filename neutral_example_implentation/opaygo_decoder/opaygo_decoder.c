#include "opaygo_decoder.h"


int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]) {
    
#ifdef RESTRICTED_DIGIT_SET_MODE
    InputToken = ConvertFromFourDigitToken(InputToken);
#endif
    
    uint16_t StartingCodeBase = GetTokenBase(StartingCode);
    uint16_t TokenBase = GetTokenBase((uint32_t)InputToken);
    uint32_t CurrentToken = PutBaseInToken(StartingCode, TokenBase);
    uint32_t MaskedToken;
    int MaxCountTry;
    int MinCountTry;
    
    int Value = DecodeBase(StartingCodeBase, TokenBase);
    
    if(Value == COUNTER_SYNC_VALUE) {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP_COUNTER_SYNC;
        MinCountTry = *LastCount - MAX_TOKEN_JUMP;
    } else {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP;
        MinCountTry = *LastCount;
    }
    
    for (int Count=0; Count <= MaxCountTry; Count++) {
        MaskedToken = PutBaseInToken(CurrentToken, TokenBase);
        if(MaskedToken == InputToken && Count > MinCountTry) {
            *LastCount = Count;
            return Value;
        }
        CurrentToken = GenerateOPAYGOToken(CurrentToken, SECRET_KEY);
    }
    
    return -1;
}
