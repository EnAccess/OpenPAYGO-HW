// --- LOOP


void loop() {
  // --- FACTORY SETUP MODE
  if(setupComplete != SETUP_COMPLETE_MAGIC_NUMBER) {
    if (Serial.available() > 0) {  // send data only when you receive data; condition in setupComplete in case the eeprom was badly initialized
      handleIncomingChar();
    }
  
    if (setupComplete == SETUP_COMPLETE_MAGIC_NUMBER) {
      initialiseEEPROMData();
      getDataEeprom();
      Serial.print("count = ");
      Serial.println(lastCount);
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
