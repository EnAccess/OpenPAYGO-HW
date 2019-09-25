// --- TIME MANAGEMENT ARDUINO

#ifdef ARDUINO_TIME_MANAGER

  void initializeTime(){
    // nothing happens, millis() doesn't need to be initialized
  }

  
  uint32_t getTimeInSeconds(){
    uint32_t nowInSeconds = millis()/1000;
    return(nowInSeconds);
  }


#endif //ARDUINO_TIME_MANAGER
