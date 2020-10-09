#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "device_parameters.h"
#include "unix_device/device_functions.h"
#include "device_payg_logic.h"
#include "opaygo_decoder/opaygo_decoder.h"

uint64_t WaitForTokenEntry() {
    uint64_t TempToken = 0;
    bool NoToken = true;
    int LastKey;
    
    while(NoToken) {
        LastKey = GetKeyPressed();
        if(LastKey == STAR_KEY) {
            if(TokenEntryAllowed()) {
                NoToken = false;
            } else {
                BlinkRedLED(1);
                #ifdef DEBUG
                printf("\nToken entry locked for %d seconds", TokenEntryLockedUntil-GetTimeInSeconds());
                #endif
            }
        } else if(LastKey == HASH_KEY) {
            if(IsActive()) {
                BlinkGreenLED(1);
                #ifdef DEBUG
                printf("\nTime Left: %d seconds", ActiveUntil-GetTimeInSeconds());
                #endif
            } else {
                BlinkRedLED(1);
            }
        }
    }
    for(int i=0; i<TOKEN_LENGTH; i++) {
        // We add the last key pressed to the token (as integer) if needed
        TempToken += GetKeyPressed()*pow(10, (TOKEN_LENGTH-1)-i);
    }
    return TempToken;
}


// Main PAYG loop
int main(int argc, const char * argv[]) {
    #ifdef DEBUG
    printf("Welcome to the OPAYGO Device Simulator\n");
    printf("We're waiting for the * character to start recording the key presses. \n(You need to press ENTER after the key presses for the simulator to work)\n(Press the '#' key to see the device activation status)\n\n");
    #endif

    LoadActivationVariables(); // We load the activation variables

    uint64_t InputToken;
    TokenData Output;
    while(1) {
        // We wait for a token to be entered
        InputToken = WaitForTokenEntry();
        // We get the activation value from the token
        Output = GetDataFromToken(InputToken, &TokenCount, &UsedTokens, StartingCode, SECRET_KEY);

        #ifdef DEBUG
        printf("\n(Token entered: %llu)", InputToken);
        printf("\n(Activation Value from Token: %d)", Output.Value); // Activation Value found in the token
        printf("\n(Count: %d)\n", Output.Count); // Count found in the token
        #endif
        
        // We update the PAYG mode (ON or OFF) and the PAYG timer based on the activation value
        UpdateDeviceStatusFromTokenValue(Output.Value, Output.Count);
    }
    
    return 0;
}

