// --- FUNCTIONS


void blinkLed(int numberOfBlinks)
{
   int i;   
   for (i = 0; i < numberOfBlinks; i++){
     digitalWrite(LED_BUILTIN, HIGH);
     delay(BLINK_PERIOD);
     digitalWrite(LED_BUILTIN, LOW);
     delay(BLINK_PERIOD);
    }
}
