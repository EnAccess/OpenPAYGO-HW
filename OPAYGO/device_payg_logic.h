#ifndef device_payg_logic_h
#define device_payg_logic_h

#include <stdio.h>
#include "device_simulator/device_function_simulator.h"

#define PAYG_DISABLE_VALUE 998

void UpdateDeviceStatusFromTokenValue(int TokenValue);
void MakeUserWaitForInvalidToken();
void UpdateActivationTime(int NumberOfDaysToAdd);
bool IsActive();

#endif 
