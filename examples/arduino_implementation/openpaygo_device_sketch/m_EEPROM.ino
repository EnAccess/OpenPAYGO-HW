// --- EEPROM

void initialiseEEPROMData() {
  EEPROM.put(SETUP_COMPLETE_ADDRESS, setupComplete);
  EEPROM.put(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.put(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.put(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.put(LAST_COUNT_ADDRESS, 0); 
  EEPROM.put(USED_TOKENS_ADDRESS, 0); 
  EEPROM.put(PAYG_DISABLED_ADDRESS, 0);
  Serial.println("Data saved in EEPROM");
}

void storeTimeStampEEPROM(uint32_t timeStampInSeconds){
  EEPROM.put(LAST_TIME_STAMP_ADDRESS, timeStampInSeconds);
}

void storeNbDisconnectionsEEPROM(){
  EEPROM.put(NB_DISCONNECTIONS_ADDRESS, nbDisconnections);
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
  EEPROM.get(USED_TOKENS_ADDRESS,usedTokens);
  EEPROM.get(LAST_TIME_STAMP_ADDRESS,lastTimeStampInSeconds);
  EEPROM.get(PAYG_DISABLED_ADDRESS,paygDisabled);
  EEPROM.get(NB_DISCONNECTIONS_ADDRESS,nbDisconnections);
}


void StoreActivationVariables()
/*
 * We store all the activation variables after a token entry
 */
{
  EEPROM.put(USED_TOKENS_ADDRESS,usedTokens);
  EEPROM.put(LAST_COUNT_ADDRESS,lastCount);
  EEPROM.put(PAYG_DISABLED_ADDRESS, paygDisabled);
}


void incrementNbDisconnectionsEeprom(){
  Serial.println("Disconnection spotted!!"); // will be displayed if DEBUG_MODE is uncommented
  getDataEeprom(); // just to be sure we have the proper nb of disconnections
  nbDisconnections++;
  storeNbDisconnectionsEEPROM();
}
