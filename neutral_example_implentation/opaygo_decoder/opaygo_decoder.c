//
//  opaygo_core_extended.c
//  OPAYGO-Unix
//
//  Created by Benjamin David on 17/09/2019.
//  Copyright © 2019 Solaris Offgrid. All rights reserved.
//

#include "opaygo_decoder.h"
#include "siphash.h"

#include <stdbool.h>

int GetActivationValueFromToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]) {

#ifdef RESTRICTED_DIGIT_SET_MODE
    InputToken = ConvertFromFourDigitToken(InputToken);
#endif

    uint16_t StartingCodeBase = GetTokenBase(StartingCode);
    uint16_t TokenBase = GetTokenBase((uint32_t)InputToken);
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
        CurrentToken = GenerateOPAYGOToken(CurrentToken, SECRET_KEY);
    }

    return -1;
}

int DecodeBase(int StartingCodeBase, int TokenBase) {
    if((TokenBase - StartingCodeBase) < 0) {
        return TokenBase + 1000 - StartingCodeBase;
    } else {
        return TokenBase - StartingCodeBase;
    }
}

int GetTokenBase(uint32_t Token) {
    return (Token % 1000);
}

uint32_t PutBaseInToken(uint32_t Token, int TokenBase) {
    return Token - (Token % 1000) + TokenBase;
}

uint32_t extractBits(uint32_t source, unsigned from, unsigned to)
{
    unsigned mask = ( (1<<(to-from+1))-1) << from;
    return (source & mask) >> from;
}

uint32_t ConvertHashToToken(uint64_t this_hash) {
    // We split the hash in two parts
    uint32_t hi_hash, lo_hash;
    hi_hash = this_hash >> 32;
    lo_hash = this_hash & 0xFFFFFFFF;

    // We XOR the two halves together
    hi_hash ^= lo_hash;

    // We reduce it to 30 bits
    uint32_t result = extractBits(hi_hash, 2, 32);
    // We reduce it to 29.5bits
    if(result > 999999999) {
        result = result - 73741825;
    }
    return result;
}

uint32_t GenerateOPAYGOToken(uint32_t LastToken, char SECRET_KEY[16]) {
    uint8_t a[8];

    a[0] = LastToken >> 24;
    a[1] = LastToken >> 16;
    a[2] = LastToken >>  8;
    a[3] = LastToken;
    a[4] = LastToken >> 24;
    a[5] = LastToken >> 16;
    a[6] = LastToken >>  8;
    a[7] = LastToken;

    uint64_t ThisHash = siphash24(a, 8, SECRET_KEY);

    // We return the conformed token
    return ConvertHashToToken(ThisHash);
}

void StoreNBitsInArray(bool* BooleanArray, uint64_t Data, uint8_t NumberOfBits, uint8_t BufferStartBit)
{
    for (int i = 0; i < NumberOfBits; i++)
    {
        BooleanArray[i+BufferStartBit] = !!(Data & (1 << ((NumberOfBits - 1 - i)))); ;
    }
}

uint32_t GetINTFromBooleanArray(bool* BooleanArray, uint8_t StartPosition, uint8_t Lenght)
{
    uint32_t Buffer = 0;
    for (int i = StartPosition; i < StartPosition+Lenght; i++) {
        Buffer = (Buffer << 1) + (BooleanArray[i] ? 1 : 0);
    }
    return Buffer;
}

uint32_t ConvertFromFourDigitToken(uint64_t FourDigitToken) {
    // This is made for 15 digit long codes converting to 9.
    // For other lengths the code needs to be adapted
    bool TokenBooleanArray[30] = {0};
    uint8_t ThisDigit;

    for(int i = 0; i < 15; i++) {
        ThisDigit = (FourDigitToken % 10) - 1;
        StoreNBitsInArray(TokenBooleanArray, ThisDigit, 2, (14-i)*2);
        FourDigitToken /= 10;
    }

    return GetINTFromBooleanArray(TokenBooleanArray, 0, 30);
}

int32_t GetActivationValueFromExtendedToken(uint64_t InputToken, uint16_t *LastCount, uint32_t StartingCode, char SECRET_KEY[16]) {

    uint32_t StartingCodeBase = GetTokenBaseExtended(StartingCode);
    uint32_t TokenBase = GetTokenBaseExtended(InputToken);
    uint64_t CurrentToken = PutBaseInTokenExtended(StartingCode, TokenBase);
    uint64_t MaskedToken;
    int MaxCountTry;

    int32_t Value = (int32_t)DecodeBaseExtended(StartingCodeBase, TokenBase);

    if(Value == COUNTER_SYNC_VALUE) {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP_COUNTER_SYNC;
    } else {
        MaxCountTry = *LastCount + MAX_TOKEN_JUMP;
    }

    for (int Count=0; Count <= MaxCountTry; Count++) {
        MaskedToken = PutBaseInTokenExtended(CurrentToken, TokenBase);
        if(MaskedToken == InputToken && Count > *LastCount) {
            *LastCount = Count;
            return Value;
        }
        CurrentToken = GenerateOPAYGOTokenExtended(CurrentToken, SECRET_KEY);
    }

    return -1;
}

uint64_t extractBitsExtended(uint64_t source, unsigned from, unsigned to)
{
    unsigned long long mask = ( (1ull<<(to-from+1ull))-1ull) << from;
    return (source & mask) >> 24;
}

uint64_t ConvertHashToTokenExtended(uint64_t this_hash) {
    // We reduce it to 40 bits
    uint64_t result = extractBitsExtended(this_hash, 24, 64);
    // We reduce it to 39.5bits
    if(result > 999999999999) {
        result = result - 99511627777;
    }
    return result;
}

uint64_t GenerateOPAYGOTokenExtended(uint64_t LastToken, char SECRET_KEY[16]) {

    uint8_t a[8];

    a[0] = LastToken >> 56;
    a[1] = LastToken >> 48;
    a[2] = LastToken >> 40;
    a[3] = LastToken >> 32;
    a[4] = LastToken >> 24;
    a[5] = LastToken >> 16;
    a[6] = LastToken >>  8;
    a[7] = LastToken;

    uint64_t ThisHash = siphash24(a, 8, SECRET_KEY);

    // We return the conformed token
    return ConvertHashToTokenExtended(ThisHash);
}

uint32_t DecodeBaseExtended(uint32_t StartingCodeBase, uint32_t TokenBase) {
    if(TokenBase < StartingCodeBase) {
        return TokenBase + 1000000 - StartingCodeBase;
    } else {
        return TokenBase - StartingCodeBase;
    }
}

uint32_t GetTokenBaseExtended(uint64_t Token) {
    return (Token % 1000000);
}

uint64_t PutBaseInTokenExtended(uint64_t Token, uint32_t TokenBase) {
    return Token - (Token % 1000000) + TokenBase;
}
