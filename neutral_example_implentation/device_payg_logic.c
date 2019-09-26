#include "device_payg_logic.h"

#include "device_function_simulator.h"
#include "opaygo_decoder/opaygo_decoder.h"
#include "device_parameters.h"

#include <stdio.h>
#include <math.h>

int InvalidTokenCount = 0;

void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount) {
    if(TokenValue == -1) {
        InvalidTokenCount++;
        UpdateInvalidTokenWaitingPeriod();
    } else {
        InvalidTokenCount = 0;
        if(TokenValue == COUNTER_SYNC_VALUE) {
            BlinkGreenLED(3); // We blink green twice to show that the token is good
        } else if(TokenValue == PAYG_DISABLE_VALUE) {
            PAYGEnabled = false;
            StoreActivationVariables();
            BlinkGreenLED(5); // We blink green twice to show that the device is active forever
        } else {
            PAYGEnabled = true;
            if(ActivationCount % 2) {
                SetTime(TokenValue);
            } else {
                AddTime(TokenValue);
            }
            StoreActivationVariables();
            BlinkGreenLED(2); // We blink green twice to show that the token is good
        }
    }
}

void UpdateInvalidTokenWaitingPeriod() {
    uint32_t Now = GetTimeInSeconds();

    // We check that it does not become unbearably long
    if(InvalidTokenCount > 9) {
        InvalidTokenCount = 9;
    }

    TokenEntryLockedUntil = Now + pow(2, InvalidTokenCount)*60;
}

bool TokenEntryAllowed() {
    if(TokenEntryLockedUntil > GetTimeInSeconds()) {
        return false;
    } else {
        return true;
    }
}


void AddTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;

    if(ActiveUntil < Now) {
        ActiveUntil = Now;
    }

    ActiveUntil += NumberOfSecondsToActivate; // We add the number of days (converted in seconds for to compare to our RTC time)
}

void SetTime(int ActivationValue) {
    uint32_t Now = GetTimeInSeconds();
    int NumberOfSecondsToActivate = (ActivationValue*3600*24) / TIME_DIVIDER;

    ActiveUntil = Now + NumberOfSecondsToActivate; // We set the number of days (converted in seconds for to compare to our RTC time)
}

bool IsActive() {
    if(PAYGEnabled) {
        if(ActiveUntil > GetTimeInSeconds()) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}
