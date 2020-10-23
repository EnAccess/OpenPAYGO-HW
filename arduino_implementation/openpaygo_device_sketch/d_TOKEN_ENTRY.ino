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
  TokenData Output;
  char incomingChar;
  if (abortedToken == false){ // abortedToken = true if a code was aborted ('*' pressed in the middle), to avoid the user to use "**" that would bring confusion
    incomingChar = getKeyPressed(); // reads every char until there is a '*' detected
  }
  
  if (incomingChar == '*' || abortedToken == true) {
    abortedToken = false; // reset abortedToken
    inputToken = getCode();
    Serial.print("activation code = "); // will only be printed if DEBUG_MODE is uncommented
    Serial.println(inputToken);
    if (inputToken == STAR_KEY_PRESSED) {
      abortedToken = true;// '*' was pressed again before the code was entirely entered (probably an error was made), the loop should start from scratch
    } else {
      Output = GetDataFromToken((uint64_t)inputToken, &lastCount, &usedTokens, startingCode, secretKey);
      // We update the PAYG mode (ON or OFF) and the PAYG timer based on the activation value
      UpdateDeviceStatusFromTokenValue(Output.Value, Output.Count);
      Serial.print("Activation value = "); // will only be printed if DEBUG_MODE is uncommented
      Serial.println(Output.Value);
      Serial.print("count = ");
      Serial.println(Output.Count);
      uint32_t activeUntilInDays = round(activeUntil/3600.0f/24.0f);
      Serial.print("Active until in days = ");
      Serial.println(activeUntilInDays);
    }
  }
}


void UpdateDeviceStatusFromTokenValue(int TokenValue, int ActivationCount) {
    if(TokenValue == -1) {
        blinkLed(15);
    } else {
        if(TokenValue == COUNTER_SYNC_VALUE) {
            blinkLed(3); // We blink green twice to show that the token is good
        } else if(TokenValue == PAYG_DISABLE_VALUE) {
            paygDisabled = 1;
            blinkLed(5);
        } else {
            paygDisabled = 0;
            if(ActivationCount % 2) {
                setTime(TokenValue);
            } else {
                addTime(TokenValue);
            }
            blinkLed(2);
        }
        StoreActivationVariables(); // We store in every case
    }
}
