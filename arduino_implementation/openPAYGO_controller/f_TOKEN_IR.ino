#ifdef IR_RECEIVER_MODE

void initializeInterface()
{
  irrecv.enableIRIn(); // Start the receiver
}



bool isDataAvailable()
{
  return(irrecv.decode(&results));
}


char getKeyPressed()
/*
 * returns the key pressed on the IR remote as a char (this function forces to put the key in a char, good practice)
 */
{
  char incomingByte = '/';
  switch(results.value)
  {
  case 0xFF9867: incomingByte = '0'; break;
  case 0xFFA25D: incomingByte = '1'; break;
  case 0xFF629D: incomingByte = '2'; break;
  case 0xFFE21D: incomingByte = '3'; break;
  case 0xFF22DD: incomingByte = '4'; break;
  case 0xFF02FD: incomingByte = '5'; break;
  case 0xFFC23D: incomingByte = '6'; break;
  case 0xFFE01F: incomingByte = '7'; break;
  case 0xFFA857: incomingByte = '8'; break;
  case 0xFF906F: incomingByte = '9'; break;
  case 0xFFB04F: incomingByte = '#'; break;
  case 0xFF6897: incomingByte = '*'; break;
//  case 0xFFFFFFFF: Serial.println("REPEAT");break;  
  default: incomingByte = '/'; // for other button
  }

  Serial.print("incoming byte = "); // decomment DEBUG_MODE to print this
  Serial.println(incomingByte); // decomment DEBUG_MODE to print this
  irrecv.resume(); // receive the next value
  delay(100);
  if (isAccepted(incomingByte)){
    return(incomingByte);
  }
  Serial.println("Char not accepted"); // decomment DEBUG_MODE to print this
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
  char a;
  for (i = 0; i < 9; i++){
    while (irrecv.decode(&results) == 0){
      if ((millis()-t0) > MAX_TIME_TOKEN_ENTRY*1000){
        return(EXCEEDED_TIME_TOKEN);
      }
    }
    // check if it can be normalized and remove from specific functions
    if (irrecv.decode(&results)){
      delay(100);
      a = getKeyPressed();
      delay(100);
    }
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
