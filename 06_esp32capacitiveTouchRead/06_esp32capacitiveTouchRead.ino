// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.

int touchVal = 9999;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop()
{
  touchVal = touchRead(T0);
  Serial.print(touchVal);
  if (touchVal < 26) {
    Serial.print(" - touched!");
  }
  Serial.println();
  delay(200);
}
