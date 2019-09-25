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

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //sets the RTC to the date & time this sketch was compiled
  }


  uint32_t getTimeInSeconds(){
    /*
     *Returns the unixtime in seconds of Now 
     */
    DateTime now = rtc.now();
    uint32_t nowInSeconds = now.unixtime();
    return(nowInSeconds);
  }


  void updateActiveUntilFromNvram()
  /*
   * Fetch the data in the NVRAM of the RTC module
   */
  { 
    uint8_t readData[4] = {0};
    rtc.readnvram(readData, 4, ACTIVE_UNTIL_NVRAM_ADDRESS); // size of the buffer = 4
    activeUntil = convertByteArrayToUint32(readData);
  }

#endif
