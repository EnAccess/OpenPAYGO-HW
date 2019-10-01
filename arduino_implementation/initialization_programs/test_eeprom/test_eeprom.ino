#include <EEPROM.h>

// EEPROM memory can be written around 100 000 times. It can be read as many times as necessary.
// UNO has 1024 bytes of EEPROM. all bytes are set as 0xFF by default
// https://www.carnetdumaker.net/articles/stocker-des-donnees-en-memoire-eeprom-avec-une-carte-arduino-genuino/

/*
 * EEPROM location:
 * Byte 0: serialCount
 * Byte 1, 2, 3, 4: serialNumber
 * Byte 5,6,7,8: startingCode
 * Byte 9 - 24 secretKey
 * Byte 25,26 lastCount
 * Byte 27,28 activationValue (in days)
 */

#define SERIAL_COUNT_ADDRESS 0
#define SERIAL_NUMBER_ADDRESS 1
#define STARTING_CODE_ADDRESS 5
#define SECRET_KEY_ADDRESS 9
#define LAST_COUNT_ADDRESS 25
#define LAST_TIME_STAMP_ADDRESS 27
#define PAYG_DISABLED_ADDRESS 31
#define NB_DISCONNECTIONS_ADDRESS 32


// initialize variables
byte serialCount;
uint32_t serialNumber;
uint32_t startingCode;
unsigned char secretKey[16];
uint16_t lastCount;
uint32_t lastTimeStampInSeconds;
uint8_t paygDisabled;
uint8_t nbDisconnections;

// read EEPROM
void setup() {
  Serial.begin(9600);
  readEeprom();
  printEeprom();
  //initializeEepromAfterFactory();
  initializeEepromToZero();
  readEeprom();
  printEeprom();
  /*initializeEepromToZero();
  readEeprom();
  printEeprom();*/
}

void loop() {
} 
