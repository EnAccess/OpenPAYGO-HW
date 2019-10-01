// --- LOOP


void loop() {

  blinkLed(3);
  Serial.print("#SN ");
  Serial.print(serialNumber);
  Serial.println();
  delay(1000);
  
  Serial.print("#SC ");
  Serial.print(startingCode);
  Serial.println();
  delay(1000);

  while (Serial.available()){
    delay(100);
    char a = Serial.read();
    Serial.print(a);
    delay(20);
  }

  Serial.print("#SK ");
  int i;
  for (i = 0; i < 16; i++){
    Serial.print(secretKey[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);

  /* FOR TEST PURPOSE
  while (Serial.available()){
    delay(100);
    char a = Serial.read();
    Serial.print(a);
    delay(20);
  }
  */
}
