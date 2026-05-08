#include <HardwareSerial.h>

HardwareSerial RS485(2);

#define RX_PIN 4
#define TX_PIN 5

void setup() {
  Serial.begin(115200);
  RS485.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("Reading full packet...");
}

void loop() {
  if (RS485.available()) {
    Serial.print("Packet: ");

    while (RS485.available()) {
      int b = RS485.read();
      Serial.print(b, HEX);
      Serial.print(" ");
    }

    Serial.println();
  }

  delay(200);
}