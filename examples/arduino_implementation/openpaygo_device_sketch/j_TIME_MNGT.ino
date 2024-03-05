// --- TIME MANAGEMENT


void handleActivationTime(){
  /*
   * Updates the TimeStamp in EEPROM if too much time passed since last timestamp
   * If the user is inactive (activeUntil passed AND PAYGenabled) => activation pin set to low
   * If the last time stamp doesn't match, the user disconnected the system (potentially to hack it) => activation pin set to low
   */
  nowInSeconds = getTimeInSeconds();
  getDataEeprom(); // updates the lastTimeStamp
  
  if (nowInSeconds > lastTimeStampInSeconds + EEPROM_TIME_UPDATE_PERIOD){ // to update the timeStamp 
    storeTimeStampEEPROM(nowInSeconds);
  }
  
  if (isActive() == 0){
    digitalWrite(PIN_ACTIVATION, LOW);
  } else {
    digitalWrite(PIN_ACTIVATION, HIGH);
  }
}


bool isActive() {
  if(paygDisabled != 1) {
      if(activeUntil > getTimeInSeconds()) {
          return true;
      } else {
          return false;
      }
  } else if (paygDisabled == 1){
      return true;
  }
}


bool lastTimeStampNotMatching(uint32_t nowInSeconds)
  /*
   * If (Now is more than lastTimeStamp + EEPROM_TIME_UPDATE_PERIOD + accepted time period) OR (Now is inferior to lastTimeStamp), it returns 1 (probably there was a cheating attempt
   */
{
  if ((nowInSeconds > lastTimeStampInSeconds + EEPROM_TIME_UPDATE_PERIOD + MAX_TIME_WITHOUT_UPDATE) | (nowInSeconds < lastTimeStampInSeconds)){
    return(1);
  }
  return(0);
}


void addTime(int activationValue) {
  uint32_t nowInSeconds = getTimeInSeconds();
  uint32_t numberOfSecondsToActivate = (uint32_t)activationValue*24*60*60/TIME_DIVIDER;
  if(activeUntil < nowInSeconds) {
      activeUntil = nowInSeconds;
  }  
  activeUntil += numberOfSecondsToActivate; // We add the number of days (converted in seconds for to compare to our RTC time)

  #ifdef RTC_MODULE_TIME_MANAGER
    storeUint32InNvram(activeUntil, ACTIVE_UNTIL_NVRAM_ADDRESS); // store ActiveUntil in the NVRAM of the RTC module
  #endif
}


void setTime(int activationValue) {
  uint32_t nowInSeconds = getTimeInSeconds();
  uint32_t numberOfSecondsToActivate = (uint32_t)activationValue*24*60*60/TIME_DIVIDER;
  activeUntil = nowInSeconds + numberOfSecondsToActivate; // We set the number of days (converted in seconds for to compare to our RTC time)
  
  #ifdef RTC_MODULE_TIME_MANAGER
    storeUint32InNvram(activeUntil, ACTIVE_UNTIL_NVRAM_ADDRESS); // store ActiveUntil in the NVRAM of the RTC module
  #endif
}


void initializeActivation()
/*
 * Check if the EEPROM stored a value 1 for PAYGDisabled
 * If the RTC module is used, check the ActiveUntil data stored in the NVRAM
 * If no RTC module, ActiveUntil is set to 0 by default
 */
{
  pinMode(PIN_ACTIVATION, OUTPUT);
  digitalWrite(PIN_ACTIVATION, LOW); // LOW by default
  EEPROM.get(PAYG_DISABLED_ADDRESS, paygDisabled);
  if (paygDisabled == 1){ // careful, EEPROM is set as 0xFF by default
    digitalWrite(PIN_ACTIVATION, HIGH);
    #ifdef RTC_MODULE_TIME_MANAGER
      activeUntil = readUint32FromNvram(ACTIVE_UNTIL_NVRAM_ADDRESS); // update activeUntil from NVRAM, in case the payg_disabled was a mistake, so that the activation is not lost
    #endif
  }
  else{
    paygDisabled = 0;
    #ifdef RTC_MODULE_TIME_MANAGER
      activeUntil = readUint32FromNvram(ACTIVE_UNTIL_NVRAM_ADDRESS); // update activeUntil from NVRAM, 0 if it is the first setup
      if (activeUntil > getTimeInSeconds()){
        digitalWrite(PIN_ACTIVATION, HIGH);
      }
    #endif
  }
}
