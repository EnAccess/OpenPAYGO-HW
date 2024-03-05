// --- TIME MANAGEMENT ARDUINO

#ifdef ARDUINO_TIME_MANAGER

void initializeTime(){
  nowInSeconds = getTimeInSeconds();
  getDataEeprom(); // updates the lastTimeStamp

  //We check that it is not a disconnection power - Arduino
  if (lastTimeStampNotMatching(nowInSeconds)){
    incrementNbDisconnectionsEeprom();
    activeUntil = 0; // will put the PIN_ACTIVATION low in the next loop
    storeTimeStampEEPROM(nowInSeconds);
  }
}


uint32_t getTimeInSeconds(){
  uint32_t nowInSeconds = millis()/1000;
  return(nowInSeconds);
}


#endif //ARDUINO_TIME_MANAGER
