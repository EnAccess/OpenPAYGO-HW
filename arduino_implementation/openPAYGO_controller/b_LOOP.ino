// --- LOOP


void loop() {
  // --- FACTORY SETUP MODE
  if(serialCount == 0) {
    if (Serial.available() > 0) {  // send data only when you receive data; condition in SerialCount in case the eeprom was badly initialized
      handleIncomingChar();
    }
  
    if ((serialNumber != 0) && (startingCode != 0) && (isSecretKeyInitialized(secretKey) == 0)) {
      serialCount = 1;
      storeDataToEeprom();
      getDataEeprom();
      blinkLed(3);
      #ifndef DEBUG_MODE
        Serial.end(); // closes the serial communication for more safety
      #endif
    }
  }
  
  // --- TOKEN INPUT MODE
  else {
    if (isDataAvailable()) {
      delay(100);
      handleIncomingKeypress();   
    }
    handleActivationTime();
  }
}
