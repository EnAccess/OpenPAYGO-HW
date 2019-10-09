void readEeprom(){
  EEPROM.get(SERIAL_COUNT_ADDRESS, serialCount);
  EEPROM.get(SERIAL_NUMBER_ADDRESS, serialNumber);
  EEPROM.get(STARTING_CODE_ADDRESS, startingCode);
  EEPROM.get(SECRET_KEY_ADDRESS, secretKey);
  EEPROM.get(LAST_COUNT_ADDRESS, lastCount);
  EEPROM.get(LAST_TIME_STAMP_ADDRESS, lastTimeStampInSeconds);
  EEPROM.get(PAYG_DISABLED_ADDRESS, paygDisabled);
  EEPROM.get(NB_DISCONNECTIONS_ADDRESS, nbDisconnections);
}

void initializeEepromToZero()
{
  byte EEPROM_SerialCount = 0;
  uint32_t EEPROM_SerialNumber = 0;
  uint32_t EEPROM_StartingCode = 0;
  unsigned char EEPROM_SecretKey[16] = {0};
  uint16_t EEPROM_lastCount = 0;
  uint32_t EEPROM_lastTimeStampInSeconds = 0;
  uint8_t EEPROM_paygDisabled = 0;
  uint8_t EEPROM_nbDisconnections = 0;

  EEPROM.put(SERIAL_COUNT_ADDRESS, EEPROM_SerialCount);
  EEPROM.put(SERIAL_NUMBER_ADDRESS, EEPROM_SerialNumber);
  EEPROM.put(STARTING_CODE_ADDRESS, EEPROM_StartingCode);
  EEPROM.put(SECRET_KEY_ADDRESS, EEPROM_SecretKey);
  EEPROM.put(LAST_COUNT_ADDRESS, EEPROM_lastCount);
  EEPROM.put(LAST_TIME_STAMP_ADDRESS, EEPROM_lastTimeStampInSeconds);
  EEPROM.put(PAYG_DISABLED_ADDRESS, EEPROM_paygDisabled);
  EEPROM.put(NB_DISCONNECTIONS_ADDRESS, EEPROM_nbDisconnections);
}

void initializeEepromAfterFactory()
{
  byte EEPROM_SerialCount = 1;
  uint32_t EEPROM_SerialNumber = 223;
  uint32_t EEPROM_StartingCode = 123456789;
  unsigned char EEPROM_SecretKey[16] = {(unsigned char)0xa2, (unsigned char)0x9a, (unsigned char)0xb8, (unsigned char)0x2e, (unsigned char)0xdc, (unsigned char)0x5f, (unsigned char)0xbb, (unsigned char)0xc4, (unsigned char)0x1e, (unsigned char)0xc9, (unsigned char)0x53, (unsigned char)0xf, (unsigned char)0x6d, (unsigned char)0xac, (unsigned char)0x86, (unsigned char)0xb1}; 
  uint16_t EEPROM_lastCount = 0;
  uint32_t EEPROM_lastTimeStampInSeconds = 0;
  uint8_t EEPROM_paygDisabled = 0;
  uint8_t EEPROM_nbDisconnections = 0;
  
  EEPROM.put(SERIAL_COUNT_ADDRESS, EEPROM_SerialCount);
  EEPROM.put(SERIAL_NUMBER_ADDRESS, EEPROM_SerialNumber);
  EEPROM.put(STARTING_CODE_ADDRESS, EEPROM_StartingCode);
  EEPROM.put(SECRET_KEY_ADDRESS, EEPROM_SecretKey);
  EEPROM.put(LAST_COUNT_ADDRESS, EEPROM_lastCount);
  EEPROM.put(LAST_TIME_STAMP_ADDRESS, EEPROM_lastTimeStampInSeconds);
  EEPROM.put(PAYG_DISABLED_ADDRESS, EEPROM_paygDisabled);
  EEPROM.put(NB_DISCONNECTIONS_ADDRESS, EEPROM_nbDisconnections);
}

void printEeprom()
{
  Serial.print("serial count = ");
  Serial.println(serialCount);

  Serial.print("serial number = ");
  Serial.println(serialNumber);

  Serial.print("starting code = ");
  Serial.println(startingCode);

  Serial.print("secret key = ");
  int i;
  for (i = 0; i < 16; i++){
    Serial.print(secretKey[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("last count = ");
  Serial.println(lastCount);

  Serial.print("last time stamp = ");
  Serial.println(lastTimeStampInSeconds);

  Serial.print("paygDisabled = ");
  Serial.println(paygDisabled);

  Serial.print("nbDisconnections = ");
  Serial.println(nbDisconnections);

  Serial.println();
}

void printAllEeprom()
{
  int i;
  for (i = 0; i < 2049; i++){
    Serial.print(i);
    Serial.print("  ");
    Serial.println(EEPROM.read(i));
  }
}
