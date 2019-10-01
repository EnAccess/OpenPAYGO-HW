// Example of using the non-volatile RAM storage on the DS1307.
// You can write up to 56 bytes from address 0 to 55.
// Data will be persisted as long as the DS1307 has battery power.

#include "RTClib.h"
RTC_DS1307 rtc;


void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  rtc.begin();


  // Routine
  uint32_t activeUntilNvram= readUint32FromNvram(0);
  Serial.print("active Until NVRAM = ");
  Serial.println(activeUntilNvram);
  uint32_t timeInitializedNvram = readUint32FromNvram(4);
  Serial.print("time initialized NVRAM = ");
  Serial.println(timeInitializedNvram);

  setNvramToZero();
  printAllNvram();

  /*
  int address = 0;
  uint32_t key1 = 123456999; //0 to initialize, 
  storeUint32InNvram(key1, 0);

  uint32_t key2 = readUint32FromNvram(address);
  Serial.print("final result = ");
  Serial.println(key2);
  */
}

void loop () {
  // Do nothing in the loop.
}
