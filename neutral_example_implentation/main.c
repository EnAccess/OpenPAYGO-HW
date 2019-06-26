#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "device_simulator/device_function_simulator.h"
#include "device_payg_logic.h"
#include "opaygo_decoder/opaygo_decoder.h"

uint32_t WaitForTokenEntry() {
    uint32_t TempToken = 0;
    bool NoToken = true;
    int LastKey;
    
    while(NoToken) {
        LastKey = GetKeyPressed();
        if(LastKey == STAR_KEY) {
            NoToken = false;
        } else if(LastKey == HASH_KEY) {
            if(IsActive()) {
                BlinkGreenLED(1);
                printf("\nTime Left: %d seconds", ActiveUntil-GetTimeInSeconds());
            } else {
                BlinkRedLED(1);
            }
        }
    }
    for(int i=0; i<9; i++) {
        // We add the last key pressed to the token (as integer) if needed
        TempToken += GetKeyPressed()*pow(10, 8-i);
    }
    return TempToken;
}

// Main PAYG loop
int main(int argc, const char * argv[]) {
    printf("Welcome to the OPAYGO Device Simulator\n");
    printf("We're waiting for the * character to start recording the key presses. \n(You need to press ENTER after the key presses for the simulator to work)\n(Press the '#' key to see the device activation status)\n\n");
    
    LoadActivationVariables(); // We load the activation variables
    
    uint32_t InputToken;
    while(1) {
        // We wait for a token to be entered
        InputToken = WaitForTokenEntry();
        printf("\n(Token entered: %u)", InputToken);
        
        // We get the activation value from the token
        int TokenValue = GetActivationValueFromToken(InputToken, &ActivationCount);
        printf("\n(Activation Value from Token: %d)", TokenValue); // Activation Value found in the token
        printf("\n(Count: %d)\n", ActivationCount); // Count found in the token
        
        // We update the PAYG mode (ON or OFF) and the PAYG timer based on the activation value
        UpdateDeviceStatusFromTokenValue(TokenValue);
    }
    
    return 0;
}

