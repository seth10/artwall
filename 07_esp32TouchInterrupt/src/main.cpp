#include <Arduino.h>

/*
This is un example howto use Touch Intrrerupts
The bigger the threshold, the more sensible is the touch
*/

int threshold = 25;
bool touchDetected = false;

void gotTouch(){
 touchDetected = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T0, gotTouch, threshold);
}

void loop(){
  if (touchDetected) {
    touchDetected = false;
    Serial.println("Touch detected");
  }
}
