#ifndef device_payg_logic_h
#define device_payg_logic_h

#include <stdio.h>
#include <math.h>
#include "device_simulator/device_function_simulator.h"
#include "opaygo_core.h"
#include "device_parameters.h"

void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount);
void UpdateInvalidTokenWaitingPeriod(void);
void SetTime(int NumberOfDaysToAdd);
void AddTime(int NumberOfDaysToAdd);
bool IsActive(void);
bool TokenEntryAllowed(void);

#endif
