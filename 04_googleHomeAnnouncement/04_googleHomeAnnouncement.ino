#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#endif

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#endif
#include <esp8266-google-home-notifier.h>

const char* ssid     = "[redacted]";
const char* password = "[redacted]";

GoogleHomeNotifier ghn;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  Serial.print("connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
  
  const char displayName[] = "Google-Home-Mini";
  IPAddress ip(192, 168, 0, 19);

  Serial.println("connecting to Google Home...");
  if (ghn.ip(ip, "en") != true) {
    Serial.println(ghn.getLastError());
    return;
  }
  Serial.print("found Google Home(");
  Serial.print(ghn.getIPAddress());
  Serial.print(":");
  Serial.print(ghn.getPort());
  Serial.println(")");
  
  if (ghn.notify("Hello, World!") != true) {
    Serial.println(ghn.getLastError());
    return;
  }
  Serial.println("Done.");
}

void loop() {
  // put your main code here, to run repeatedly:

}
