#include <HardwareSerial.h>

HardwareSerial RS485(2);

void setup() {
  Serial.begin(115200);
  RS485.begin(9600, SERIAL_8N1, 4, 5);

  Serial.println("Vallox sniffer");
}

void loop() {

  static int bytePos = 0;

  while (RS485.available()) {

    uint8_t b = RS485.read();

    // Uusi kehys alkaa aina DOMAIN-arvosta 0x01
    if (b == 0x01 && bytePos != 0) {
      Serial.println();
      bytePos = 0;
    }

    if (b < 0x10)
      Serial.print("0");

    Serial.print(b, HEX);
    Serial.print(" ");

    bytePos++;
  }
}
