#include <Wire.h>

#define SLAVE_ADDRESS 9

int receivedData = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // Your slave device's main loop code can go here
}

void receiveEvent() {
  while (Wire.available()) {
    receivedData = Wire.read();
    Serial.println("Received data at slave: " + String(receivedData));

    // Send the received data back to the master
    Wire.beginTransmission(SLAVE_ADDRESS);
    Wire.write(receivedData);
    Wire.endTransmission();
  }
}

#include <Wire.h>

#define SLAVE_ADDRESS 9

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  int dataToSend = 42;

  // Send data to the slave
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(dataToSend);
  Wire.endTransmission();

  delay(500);  // Wait for the slave to process

  // Request data from the slave
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  while (Wire.available()) {
    int receivedData = Wire.read();
    Serial.println("Received data from slave: " + String(receivedData));
  }

  delay(1000);  // Wait before the next iteration
}
