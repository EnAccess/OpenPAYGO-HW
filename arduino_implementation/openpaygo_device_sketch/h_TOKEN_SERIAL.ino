#ifdef SERIAL_MODE

void initializeInterface()
{
  Serial.begin(9600); // Careful, when using the arduino pro mini 3.3V, the baud rate of the monitor must be set to 4800 to be understandable
  while (!Serial) {
  ; // wait for serial port to connect
  }
}



bool isDataAvailable()
{
  return(Serial.available());
 }


char getKeyPressed()
/*
 * returns the key pressed on the IR remote as a char (this function forces to put the key in a char, good practice)
 */
{
  char incomingByte = Serial.read();    // read the incoming byte
  Serial.println(incomingByte);
  if (isAccepted(incomingByte)){
    return(incomingByte);
  }
  //Serial.println("Char not accepted");
  return(NON_ACCEPTED_CHAR);
}


uint32_t getCode(){
  /*
   * get the coming 9 keys pressed and return the corresponding 9 digits number, as a uint32_t
   * if '*' is pressed during the process, the operation is cancelled and the function returns -1
   */
  uint32_t t0 = millis(); 
  int codeArray[9] = {0};
  int i;
  for (i = 0; i < 9; i++){
    while (Serial.available() == 0){
      if ((millis()-t0) > MAX_TIME_TOKEN_ENTRY*1000){
        return(EXCEEDED_TIME_TOKEN);
      }
    }
    char a = getKeyPressed();
    if (a == '*'){
      return(STAR_KEY_PRESSED);
    }
    else if (a == NON_ACCEPTED_CHAR){
      i--; // if the char was not valid, the user should press the key again
    }
    else if (a != '\n'){
      codeArray[i] = (int)(a-'0'); // convert ascii into int
    }
  }
  return(convertArrayToUint32(codeArray));
}


#endif
