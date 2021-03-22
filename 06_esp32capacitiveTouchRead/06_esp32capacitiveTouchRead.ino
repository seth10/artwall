// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.

int touchVal = 9999;
int touchCount = 0;
boolean currentlyTouched = false;
int touchedTimes = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop()
{
  touchVal = touchRead(T0);
  Serial.print(touchedTimes);
  Serial.print(" - ");
  Serial.print(touchVal);
  if (touchVal < 26) {
    touchCount++;
  } else {
    touchCount = 0;
  }
  Serial.print(" - ");
  Serial.print(touchCount);
  
  if (touchCount >= 3) {
    Serial.print(" - touched!");
    if (!currentlyTouched) {
      currentlyTouched = true;
      touchedTimes++;
    }
  } else {
    currentlyTouched = false;
  }
  
  Serial.println();
  delay(100);
}
