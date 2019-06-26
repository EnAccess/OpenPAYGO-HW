#ifndef device_function_simulator_h
#define device_function_simulator_h

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define STAR_KEY -1
#define HASH_KEY -2

// Device parameters (to be stored in Flash/EEPROM)
extern int ActivationCount;
extern bool PAYG_ON;
extern uint32_t ActiveUntil;

void BlinkRedLED(int NumberOfBlinks);
void BlinkGreenLED(int NumberOfBlinks);
int GetKeyPressed();
void LoadActivationVariables();
void StoreActivationVariables();
uint32_t  GetTimeInSeconds();

#endif
