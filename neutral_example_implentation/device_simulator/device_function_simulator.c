#include "device_function_simulator.h"
#include "getch.h"

// Device parameters (to be stored in Flash/EEPROM)
int TokenCount = 1;
bool PAYGEnabled = true;
uint32_t ActiveUntil = 0;
uint32_t TokenEntryLockedUntil = 0;

// This is just for displaying the activation status in the simulater WaitForTokenEntry function
extern bool IsActive(void);

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
    // We load TokenCount
    // We load PAYGEnabled
    // We load ActiveUntil
    // We load TokenEntryLockedUntil
}

void StoreActivationVariables() {
    // We store TokenCount
    // We store PAYGEnabled
    // We store ActiveUntil
    // We store TokenEntryLockedUntil
}

uint32_t GetTimeInSeconds() {
    return (uint32_t) time(NULL);
}
