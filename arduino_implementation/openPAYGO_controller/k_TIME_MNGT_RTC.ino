// --- TIME MANAGEMENT RTC MODULE


#ifdef RTC_MODULE_TIME_MANAGER

  void initializeTime(){
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
    while (1);
    }
    
    if (! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
    }

    //We check that it is not a disconnection power - Arduino
    uint32_t nvramCheck = readUint32FromNvram(TIME_INITIALIZATION_NVRAM_ADDRESS);
    if (nvramCheck == 0){ // it is the first setup of the Arduino
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //sets the RTC to the date & time this sketch was compiled
      DateTime now = rtc.now();
      timeInitializationRtc = now.unixtime();
      storeUint32InNvram(timeInitializationRtc, TIME_INITIALIZATION_NVRAM_ADDRESS);
    } else{ // a disconnection happened
      timeInitializationRtc = nvramCheck;
      incrementNbDisconnectionsEeprom();
      storeTimeStampEEPROM(getTimeInSeconds()); // to avoid counting twice the disconnection if the previous TimeStamp was too long ago
    }
  }


  uint32_t getTimeInSeconds(){
    /*
     *Returns the unixtime in seconds of Now 
     */
    DateTime now = rtc.now();
    uint32_t nowInSeconds = (now.unixtime() - timeInitializationRtc); // we substract the init time so that it's easier to read when debugging, and works the same as Arduino Time mgt
    return(nowInSeconds);
  }


  void storeUint32InNvram(uint32_t toStore, int address){
    uint8_t arrayBytes[4];
    convertUint32ToUint8Array(toStore, arrayBytes);
    rtc.writenvram(address, arrayBytes, 4);
  }


  uint32_t readUint32FromNvram(int address){
    uint8_t readData[4] = {0};
    rtc.readnvram(readData, 4, address);
    return(convertByteArrayToUint32(readData));
  }

#endif
