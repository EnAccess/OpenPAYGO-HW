// --- PRE PROCESSER

/*
 * Modifications added to v3.1:
 * Activation removed from EEPROM [DONE]
 * Use the updated library [DONE]
 * Description onglet removed [DONE]
 * New onglet EEPROM [DONE]
 * si batt est détachée, activation à 0 ==> enlevée de l'EEPROM [DONE]
*/

// CHOOSE INTERFACE
//#define KEYBOARD_MODE
#define IR_RECEIVER_MODE
//#define MEMBRANE_KEYPAD_MODE


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



// LIBRARIES
#include "opaygo_decoder.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <EEPROM.h>  // https://www.carnetdumaker.net/articles/stocker-des-donnees-en-memoire-eeprom-avec-une-carte-arduino-genuino/
#include <string.h>



// VALUES
#define BLINK_PERIOD 250 // in ms, actually half period
#define SERIAL_COUNT_ADDRESS 0
#define SERIAL_NUMBER_ADDRESS 1
#define STARTING_CODE_ADDRESS 5
#define SECRET_KEY_ADDRESS 9
#define LAST_COUNT_ADDRESS 25
#define ACTIVATION_VALUE_ADDRESS 27
#define SERIAL_NUMBER_TYPE 1
#define STARTING_CODE_TYPE 2
#define SECRET_KEY_TYPE 3
#define DISABLING_PAYGO_MODE 998
#define STAR_KEY_PRESSED -1
#define NON_ACCEPTED_CHAR -2


// VARIABLES FUNCTION FACTORY SETUP
byte serialCount = 0; // a boolean was enough, but booleans are stored in bytes...
uint32_t serialNumber = 0;
uint32_t startingCode = 0;
unsigned char secretKey[16] = {0};


// VARIABLES FUNCTION TOKEN ENTRY
uint32_t activationCode = 0; // used to be uint64_t
uint16_t lastCount = 0;
bool abortedToken = false;
char incomingChar1 = 0;
int activationValue = 0;
