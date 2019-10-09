// --- FUNCTIONS - FACTORY SETUP MODE

void handleIncomingChar() {
  delay(100); // indispensable to have Serial.available work properly (miscount otherwise)
  char incomingChar = getByteSent();
  if (incomingChar == '#'){
      int typeData = getTypeData();
      if (typeData == SERIAL_NUMBER_TYPE){
        getByteSent(); // space
        serialNumber = getSerialNumber();
      }
      else if (typeData == STARTING_CODE_TYPE){
        getByteSent(); // space
        startingCode = getStartingCode();
      }
      else if (typeData == SECRET_KEY_TYPE){ 
        getByteSent(); // space 
        updateSecretKey(secretKey);
      }
    Serial.flush();  
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


int getTypeData(){
  /*
   * Return a different int depending on what it receives after #:
   * If "SN" => 1
   * If "SC" => 2
   * If "SK" => 3
   * Else => -1
   */
  getByteSent();  // no need to read this byte, they all correspons to 'S' (SN, or SC, or SK)
  
  char incomingByte = getByteSent();
  if (incomingByte == 'N'){
    return(SERIAL_NUMBER_TYPE);
  }
  else if (incomingByte == 'C'){
    return(STARTING_CODE_TYPE);
  }
  else if (incomingByte == 'K'){
    return(SECRET_KEY_TYPE);
  }
  else {
    return(-1);   // error
  }
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
  return(convertArrayToUint32(codeArray));
}


uint32_t getSerialNumber()
/*
 * get the coming keys until we see a JUMP (Line Feed or '\n') appears.
 * returns the SN as a uint32_t
 */
{
  int codeArray[9] = {0};
  int i;
  for (i = 0; i < 9; i++){
    char a = getByteSent();
    if ((a == '\n') || (a == '\r')){
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
    if (char2 == ' '){
      secretKey[i] = (unsigned char)strtol(&char1, NULL, 16);
    }
    else{
      int sum = 16*(unsigned char)strtol(&char1, NULL, 16) + (unsigned char)strtol(&char2, NULL, 16); // convert the text into the proper int
      secretKey[i] = sum;
      getByteSent(); // space
    }
    delay(100);
  }
  return 0;
}


int isSecretKeyInitialized(unsigned char tab[16])
/*
 * returns 1 if initialized (all chars at 0), 0 otherwise
 */
{
  int k;
  for (k = 0; k < 16; k ++){
    if (tab[k] != 0){
      return(0);
    }
  }
  return(1);
}
