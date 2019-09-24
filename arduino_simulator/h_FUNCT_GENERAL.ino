// --- FUNCTIONS - GENERAL


uint32_t convertArrayToUint32(int arrayToConvert[9]){
  int i = 0;
  uint32_t uint32 = 0;
  for (i = 0 ; i < 9 ; i++){
    uint32 = 10*uint32 + arrayToConvert[i];
  }
  return(uint32);
}



void blinkLed(int numberOfBlinks)
/*
 * Makes the inbuilt LED blinks as many times as the input said
 */
{
   int i; 
   for (i = 0; i < numberOfBlinks; i++)
   {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(BLINK_PERIOD);
    digitalWrite(LED_BUILTIN, LOW);
    delay(BLINK_PERIOD);
    }
}
