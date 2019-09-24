// --- EEPROM

void storeDataToEEPROM() {
  EEPROM.put(SERIAL_COUNT_ADDRESS,serialCount);
  EEPROM.put(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.put(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.put(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.put(LAST_COUNT_ADDRESS,lastCount); 
}

void getDataEeprom()
/*
 * get all the data from the EEPROM and put it in the associated RAM variables
 */
{
  EEPROM.get(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.get(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.get(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.get(LAST_COUNT_ADDRESS,lastCount);
  EEPROM.get(ACTIVATION_VALUE_ADDRESS,activationValue); // Do not read unless the time keeps running when the MCU is off
  blinkLed(3);
}
