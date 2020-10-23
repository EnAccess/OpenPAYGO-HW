// --- CONFIGURATION

// CHOOSE ONE INTERFACE (comment the others)
//#define KEYBOARD_MODE
//#define IR_RECEIVER_MODE
//#define MEMBRANE_KEYPAD_MODE
#define SERIAL_MODE

// CHOOSE ONE TIME MANAGER (comment the other)
#define ARDUINO_TIME_MANAGER
//#define RTC_MODULE_TIME_MANAGER

// CHOOSE DEBUG MODE (decomment it to use the Serial Communication)
// #define DEBUG_MODE

// CHOOSE TIME DIVIDER
#define TIME_DIVIDER 1


// --- LIBRARY IMPORTS

// SPECIFIC
#ifdef KEYBOARD_MODE
  #include <PS2Keyboard.h> // Keyboard: S2Keyboard-master library or https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  const int DataPin = 2; // white wire USB
  const int IRQpin =  3; // green wire USB
  PS2Keyboard keyboard;
#endif

#ifdef IR_RECEIVER_MODE
  #include "IRremote.h" // IR receiver
  const int ReceiverPin = 3;
  IRrecv irrecv(ReceiverPin);     // create instance of 'irrecv'
  decode_results results;      // create instance of 'decode_results'
#endif

#ifdef MEMBRANE_KEYPAD_MODE
  #include <Keypad.h>
  const byte ROWS = 4;
  const byte COLS = 3;
  char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
  };
  byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {5, 4, 3}; //connect to the column pinouts of the keypad
  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
  char key = '/'; // global variable
  bool keyWaitingToBeRead = false;
#endif

#ifdef RTC_MODULE_TIME_MANAGER
  #include "RTClib.h"
  RTC_DS1307 rtc; // for Arduino Pro Mini, SDA -> A4  SCL -> A5
  #define ACTIVE_UNTIL_NVRAM_ADDRESS 0 // 56 bytes address from 0 to 55 in the NVRAM
  #define TIME_INITIALIZATION_NVRAM_ADDRESS 4
  uint32_t timeInitializationRtc = 0;
#endif


extern "C" {
  #include <opaygo_decoder.h>
}
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <EEPROM.h>
#include <string.h>


// CONSTANTS
#define BLINK_PERIOD 250 // in ms, actually half period
// EEPROM
#define SETUP_COMPLETE_ADDRESS 0
#define SERIAL_NUMBER_ADDRESS 1
#define STARTING_CODE_ADDRESS 5
#define SECRET_KEY_ADDRESS 9
#define LAST_COUNT_ADDRESS 25
#define LAST_TIME_STAMP_ADDRESS 27
#define PAYG_DISABLED_ADDRESS 31
#define NB_DISCONNECTIONS_ADDRESS 32
#define USED_TOKENS_ADDRESS 33
//Time management
#define PIN_ACTIVATION 10
#define EEPROM_TIME_UPDATE_PERIOD 100 // put it back to 3600 //in sec, the EEPROM is updated every 1hour for the time => 43 800 times in 5 years, max for Arduino EEPROM is 100 000 times (estimation)
#define MAX_TIME_WITHOUT_UPDATE 25 // put it back to, //in sec, make sure it is more than MAX_TIME_TOKEN_ENTRY
// Factory Setup
#define SETUP_COMPLETE_MAGIC_NUMBER 174
#define SERIAL_NUMBER_TYPE 1
#define STARTING_CODE_TYPE 2
#define SECRET_KEY_TYPE 3
// Token Entry
#define STAR_KEY_PRESSED -1
#define NON_ACCEPTED_CHAR -2
#define EXCEEDED_TIME_TOKEN -3
#define MAX_TIME_TOKEN_ENTRY 20 // in sec


// GLOBAL VARIABLES FACTORY SETUP
uint8_t setupComplete = 0;
uint32_t serialNumber = 0;
uint32_t startingCode = 0;
unsigned char secretKey[16] = {0};

// GLOBAL VARIABLES TOKEN ENTRY
uint32_t inputToken = 0;
uint16_t lastCount = 0;
uint16_t usedTokens = 0;
bool abortedToken = false;

// GLOBAL VARIABLES ACTIVATION & TIME
uint32_t activeUntil = 0;
uint32_t nowInSeconds; // uint32_t can go up to 133 years
uint32_t lastTimeStampInSeconds = 0;
uint8_t paygDisabled = 0; //uint8_t because we need to store a byte in EEPROM
uint8_t nbDisconnections = 0; //uint8_t because we need to store a byte in EEPROM
