// --- PRE-PROCESSOR


#define BLINK_PERIOD 250


// Codes to send to the OpenPAYG Controller, to be modified for each OpenPAYG Controller
static const unsigned char secretKey[16] = {(unsigned char)0xa2, (unsigned char)0x9a, (unsigned char)0xb8, (unsigned char)0x2e, (unsigned char)0xdc, (unsigned char)0x5f, (unsigned char)0xbb, (unsigned char)0xc4, (unsigned char)0x1e, (unsigned char)0xc9, (unsigned char)0x53, (unsigned char)0xf, (unsigned char)0x6d, (unsigned char)0xac, (unsigned char)0x86, (unsigned char)0xb1};
static uint32_t startingCode = 123456789;
static uint32_t serialNumber = 223;


void setup() {  
  Serial.begin(9600); // send data with baud rate of 4 800 with Arduino Uno and it will be received as 9 600 by the pro mini 3.3V
  while (!Serial) {
    ; // wait for serial port to connect
  }
  pinMode(LED_BUILTIN, OUTPUT);
  
}
