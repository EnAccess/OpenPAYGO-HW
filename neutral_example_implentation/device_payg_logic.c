#include "device_payg_logic.h"

int InvalidTokenCount = 0;

void UpdateDeviceStatusFromTokenValue(int TokenValue) {
    if(TokenValue == -1) {
        InvalidTokenCount++;
        MakeUserWaitForInvalidToken();
    } else {
        InvalidTokenCount = 0;
        if(TokenValue == PAYG_DISABLE_VALUE) {
            PAYG_ON = false;
            StoreActivationVariables();
            BlinkGreenLED(5); // We blink green twice to show that the device is active forever
        } else {
            PAYG_ON = true;
            UpdateActivationTime(TokenValue);
            StoreActivationVariables();
            BlinkGreenLED(2); // We blink green twice to show that the token is good
        }
    }
}

void MakeUserWaitForInvalidToken() {
    // We check that it does not become unbearably long, capping it at 100*10 seconds, or about 17 minutes
    if(InvalidTokenCount > 100) {
        InvalidTokenCount = 100;
    }
    for(int i=0;i<InvalidTokenCount;i++) {
        BlinkRedLED(10); // We blink the red LED 10 times to show that the token is bad and make the user wait (1 second per blink)
    }
}

void UpdateActivationTime(int NumberOfDaysToAdd) {
    uint32_t Now = GetTimeInSeconds();
    
    if(ActiveUntil < Now) {
        ActiveUntil = Now;
    }
    
    ActiveUntil += NumberOfDaysToAdd*3600*24; // We add the number of days (converted in seconds for to compare to our RTC time)
}

bool IsActive() {
    if(PAYG_ON) {
        if(ActiveUntil > GetTimeInSeconds()) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}
