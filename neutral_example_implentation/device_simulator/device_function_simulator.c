#include "device_function_simulator.h"
#include "getch.h"

// Device parameters (to be stored in Flash/EEPROM)
int ActivationCount = 0;
bool PAYG_ON = true;
uint32_t ActiveUntil = 0;

// This is just for displaying the activation status in the simulater WaitForTokenEntry function
extern bool IsActive();

void BlinkRedLED(int NumberOfBlinks) {
    printf("\nRed LED Blinked %d times!\n", NumberOfBlinks);
}

void BlinkGreenLED(int NumberOfBlinks) {
    printf("\nGreen LED Blinked %d times!\n", NumberOfBlinks);
}

int GetKeyPressed() {
    char this_char = getch();
    switch (this_char) {
        case '*':
            return STAR_KEY;
            break;
            
        case '#':
            return HASH_KEY;
            break;
            
        default:
            return (int) (this_char - '0'); // this_char is now an int
            break;
    }
}


void LoadActivationVariables() {
    // We load Activation Count
    // We load PAYG ON
    // We load ActiveUntil
}

void StoreActivationVariables() {
    // We store Activation Count
    // We store PAYG ON
    // We store ActiveUntil
}

uint32_t GetTimeInSeconds() {
    return (uint32_t) time(NULL);
}
