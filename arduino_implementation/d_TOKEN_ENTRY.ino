// --- FUNCTIONS - TOKEN ENTRY MODE


bool isAccepted(char incomingByte)
/*
 * Checks if the character belongs to the correct list of accepted chaaracters (IR receivers have a lot of receiving mistakes)
 */
{
  char foo[] = { '*', '#', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  if (memchr(foo, incomingByte, sizeof(foo)))
  {
    blinkLed(1); // to indicate to the user that a correct char was read
    return(1);
  }
  return(0);
}

void handleIncomingKeypress() {
  if (abortedToken == false){ // abortedToken = true if a code was aborted ('*' pressed in the middle), to avoid the user to use "**" that would bring confusion
    incomingChar1 = getKeyPressed(); // reads every char until there is a '*' detected
  }
  
  if (incomingChar1 == '*' || abortedToken == true) {
    abortedToken = false; // reset abortedToken
    activationCode = getCode();
    Serial.print("activation code = ");
    Serial.println(activationCode);
    if (activationCode == STAR_KEY_PRESSED){
      abortedToken = true;// '*' was pressed again before the code was entirely entered (probably an error was made), the loop should start from scratch
    }
    else{
      int activationValue = GetActivationValueFromToken((uint64_t)activationCode, &lastCount, startingCode, secretKey);
      Serial.print("Activation value = ");
      Serial.println(activationValue);
      Serial.print("count = ");
      Serial.println(lastCount);
      handleActivation(activationValue);
    }
  }
}



void handleActivation(int activationValue){
  /*
   * blinks 10 times if code not valid (or already typed)
   * 5 times if code is PAYG disabled
   * 2 times if code is valid (including re-enable PAYG for 0)
   */
  if (activationValue == -1){
    blinkLed(10);
  }
  else{
    EEPROM.put(LAST_COUNT_ADDRESS,lastCount);
    
    if (activationValue == DISABLING_PAYGO_MODE){
      paygDisabled = 1;
      digitalWrite(PIN_ACTIVATION, HIGH);
      EEPROM.put(PAYG_DISABLED_ADDRESS, paygDisabled);
      blinkLed(5);
    }
    else {
      enablePaygInEeprom();
      #ifdef ADD_TIME
        addTime(activationValue);
      #endif
      #ifdef SET_TIME
        setTime(activationValue);
      #endif
      digitalWrite(PIN_ACTIVATION, HIGH);
      blinkLed(2);
    }
  }
}
