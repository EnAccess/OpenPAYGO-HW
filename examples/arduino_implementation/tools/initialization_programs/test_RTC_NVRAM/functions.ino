void printnvram(uint8_t address) {
  Serial.print("Address 0x");
  Serial.print(address, HEX);
  Serial.print(" = 0x");
  Serial.println(rtc.readnvram(address), HEX);
}

void printAllNvram(){
  Serial.println("Current NVRAM values:");
  for (int i = 0; i < 55; ++i) {
     printnvram(i);
  }
}


void setNvramToZero(){
  int i;
  for (i = 0; i < 56; i++){
    rtc.writenvram(i, 0x00);
  }
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
