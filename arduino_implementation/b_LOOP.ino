// --- LOOP


void loop() {
  
  if(serialCount == 0) {
    
    // --- FACTORY SETUP MODE
    if (Serial.available() > 0) {  // send data only when you receive data; condition in SerialCount in case the eeprom was badly initialized
      delay(100); // indispensable to have Serial.available work properly (miscount otherwise)
      char incomingChar = getByteSent();
      handleIncomingChar(incomingChar);
    }
  
    if ((serialNumber != 0) && (startingCode != 0) && (isSecretKeyInitialized(secretKey) == 0)) {
      serialCount = 1;
      storeDataToEEPROM();
      Serial.println("Data saved in EEPROM");
      Serial.end();
    }
  } else {
    // --- TOKEN INPUT MODE
    if (isDataAvailable()) {
      delay(100);
      handleIncomingKeypress();   
    }
  }
}
