// --- FUNCTIONS - FACTORY SETUP MODE

void handleIncomingChar() {
  delay(100); // indispensable to have Serial.available work properly (miscount otherwise)
  char incomingChar = getByteSent();
  if (incomingChar == '#') {
      serialNumber = getSerialNumber();
      Serial.print("\nSN:");
      Serial.print(serialNumber);
      startingCode = getStartingCode();
      Serial.print("\nSC:");
      Serial.print(startingCode);
      updateSecretKey(secretKey);
      Serial.print("\nSK:");
      for (int i = 0; i < 16; i++) {
        if (secretKey[i] <= 0x0F) Serial.print("0");
        Serial.print(secretKey[i], HEX);
      }
      Serial.println("\n");
      Serial.flush();
      setupComplete = SETUP_COMPLETE_MAGIC_NUMBER;
  }
}


char getByteSent()
/*
 * returns the char sent through UART (this function forces to put the key in a char, good practice)
 */
{
  char thisIncomingByte = Serial.read();    // read the incoming byte
  delay(10);
  return(thisIncomingByte);
}



uint32_t getStartingCode()
/*
 * get the coming 9 keys pressed and return the corresponding 9 digits number, as a uint32_t
 * the starting code is always a 9 digits key
 */
{
  int codeArray[9] = {0};
  int i;
  for (i = 0; i < 9; i++){
    char a = getByteSent();
    codeArray[i] = (int)(a-'0');
  }
  getByteSent(); // We read the ";" separator
  return(convertArrayToUint32(codeArray));
}


uint32_t getSerialNumber()
/*
 * get the coming keys until we see a ";" character appears.
 * returns the SN as a uint32_t
 */
{
  int codeArray[9] = {0};
  int i;
  for (i = 0; i < 9; i++){
    char a = getByteSent();
    if (a == ';') {
      int j;
      for (j = 8; j > 8-i; j--){ // in case we spot a JUMP and the SN is less than 9 digits , we make sure it is pushed to the right of the tab
        codeArray[j] = codeArray[i+j-9];
      }
      int k;
      for (k = 0; k < 9 - i; k++){ // make sure the other 
        codeArray[k] = 0;
      }
      return(convertArrayToUint32(codeArray));
    }
    else{
      codeArray[i] = (int)(a-'0');
    }
  }
  return(convertArrayToUint32(codeArray));
}


int updateSecretKey(unsigned char secretKey[16])
/*
 * update the array secretKey with the next 16 bytes read
 * the uart sends each char in the form of 0xff, therefore we have to read two bytes, then transform it into an int, and store it in the array
 * returns updated array
 */
{
  int i;
  for (i = 0; i < 16; i++){
    char char1 = getByteSent();
    char char2 = getByteSent();
    int sum = 16*(unsigned char)strtol(&char1, NULL, 16) + (unsigned char)strtol(&char2, NULL, 16); // convert the text into the proper int
    secretKey[i] = sum;
    delay(100);
  }
  return 0;
}
