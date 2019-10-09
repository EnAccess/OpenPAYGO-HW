// --- FUNCTIONS - GENERAL


uint32_t convertArrayToUint32(int arrayToConvert[9]){
  int i = 0;
  uint32_t uint32 = 0;
  for (i = 0 ; i < 9 ; i++){
    uint32 = 10*uint32 + arrayToConvert[i];
  }
  return(uint32);
}


uint32_t convertByteArrayToUint32(uint8_t arrayToConvert[4]){
  uint32_t low1 = arrayToConvert[0];
  uint32_t low2 = arrayToConvert[1];
  low2 = low2 << 8;
  uint32_t high1 = arrayToConvert[2];
  high1 = high1 << 16;
  uint32_t high2 = arrayToConvert[3];
  high2 = high2 << 24;
  uint32_t result = low1 + low2 + high1 + high2;
  return(result);
}


void convertUint32ToUint8Array (uint32_t uint32ToConvert, uint8_t arrayBytes[4])
{
  byte low1 = uint32ToConvert;
  byte low2 = uint32ToConvert >> 8;
  byte high1 = uint32ToConvert >> 16;
  byte high2 = uint32ToConvert >> 24;
  arrayBytes[0] = low1;
  arrayBytes[1] = low2;
  arrayBytes[2] = high1;
  arrayBytes[3] = high2;
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
