#ifndef device_payg_logic_h
#define device_payg_logic_h

#include <stdbool.h>

void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount);
void UpdateInvalidTokenWaitingPeriod(void);
void SetTime(int NumberOfDaysToAdd);
void AddTime(int NumberOfDaysToAdd);
bool IsActive(void);
bool TokenEntryAllowed(void);

#endif
