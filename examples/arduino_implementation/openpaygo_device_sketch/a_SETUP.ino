// --- SETUP


void setup()
{
  #ifdef DEBUG_MODE
    Serial.begin(9600);
  #endif
  delay(1000);
  initializeInterface();
  pinMode(LED_BUILTIN, OUTPUT);

  //updates the RAM with the EEPROM values if there are correct
  EEPROM.get(SETUP_COMPLETE_ADDRESS, setupComplete);
  if (setupComplete == SETUP_COMPLETE_MAGIC_NUMBER) {    // if setupComplete == SETUP_COMPLETE_MAGIC_NUMBER, we consider the data in EEPROM is safe and complete, therefore we use it to initialize the RAM, otherwise we wait for UART communication
    getDataEeprom();
  } 
  else { // EEPROM was not (or incorrectly) initiated  
    Serial.begin(9600); // Careful, when using the arduino pro mini 3.3V, the baud rate of the monitor must be set to 4800
    while (!Serial) {
    ; // wait for serial port to connect
    }
    Serial.print("FACTORY SETUP MODE"); 
    // The command for the factory setup mode should be: #<SERIAL_NUMBER>;<STARTING_CODE>;<SECRET_KEY> 
    // For example #1234;123456789;a29ab82edc5fbbc41ec9530f6dac86b1
  }
  initializeTime();
  initializeActivation();
}
