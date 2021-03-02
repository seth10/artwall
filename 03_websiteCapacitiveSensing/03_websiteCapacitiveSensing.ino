#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "03_websiteCapacitiveSensing.h"

const char* ssid = "[redacted]";
const char* password = "[redacted]";

ESP8266WebServer server(80);

const int IN = D1;
const int OUT = D2;

const int touchVal = 7;

long sensVal = 0;
int consecutiveTouchMeasurements = 0;

char webpage[500];

void handleRoot() {
//  snprintf(webpage, sizeof(webpage), WEBPAGE_TEMPLATE, consecutiveTouchMeasurements);
  server.send(200, "text/html", WEBPAGE_TEMPLATE);
}
void handleData() {
  char str[8];
  itoa(consecutiveTouchMeasurements, str, 10);
  server.send(200, "text/plain", str);
}

void setup() {
  pinMode(IN, INPUT);
  pinMode(OUT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
  
  digitalWrite(OUT, LOW);
  delay(10);

  long startTime = micros();

  digitalWrite(OUT, HIGH);
  while (digitalRead(IN) == LOW) ;
  sensVal = micros() - startTime;
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
