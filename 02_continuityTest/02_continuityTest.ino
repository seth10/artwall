const int IN = D1;

void setup() {
  pinMode(IN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(100);
}

void loop() {
  if (digitalRead(IN) == LOW) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(10);
}
