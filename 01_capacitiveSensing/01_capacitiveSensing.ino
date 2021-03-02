const int IN = D1;
const int OUT = D2;

const int touchVal = 7;

int consecutiveTouchMeasurements = 0;

void setup() {
  pinMode(IN, INPUT);
  pinMode(OUT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(100);
}

void loop() {
  digitalWrite(OUT, LOW);
  delay(10);

  long startTime = micros();

  digitalWrite(OUT, HIGH);
  while (digitalRead(IN) == LOW) ;
  long sensVal = micros() - startTime;
  Serial.println(sensVal);

  if (sensVal > touchVal) {
    consecutiveTouchMeasurements++;
  } else {
    consecutiveTouchMeasurements = 0;
  }

  if (consecutiveTouchMeasurements > 5) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
