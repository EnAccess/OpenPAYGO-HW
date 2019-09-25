// --- SETUP


void setup()
{
  #ifdef TEST_MODE
    Serial.begin(9600);
  #endif
  delay(1000);
  initializeInterface();
  pinMode(LED_BUILTIN, OUTPUT);

  //updates the RAM with the EEPROM values if there are correct
  EEPROM.get(SERIAL_COUNT_ADDRESS, serialCount);
  if (serialCount == 1){    // if serialCount == 1, we consider the data in EEPROM is safe and complete, therefore we use it to initialize the RAM, otherwise we wait for UART communication
    getDataEeprom();
  } 
  else{ // serialCount == 0 if EEPROM was not (or wrongly) initiated  
    Serial.begin(9600); // Careful, when using the arduino pro mini 3.3V, the baud rate of the monitor must be set to 4800 to be understandable
    while (!Serial) {
    ; // wait for serial port to connect
    }
  }
  pinMode(PIN_ACTIVATION, OUTPUT);
  digitalWrite(PIN_ACTIVATION, LOW);
  initializeTime();
  initializeActivation();
}
