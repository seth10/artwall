#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FS.h>
#include "SpotifyClient.h"
#include "settings.h"

SpotifyClient client(clientId, clientSecret, redirectUri);
SpotifyData data;
SpotifyAuth auth;

String currentImageUrl = "";
long lastUpdate = 0;
const int threshold = 25;
bool touchDetected = false;

void saveRefreshToken(String refreshToken);
String loadRefreshToken();

void gotTouch(){
 touchDetected = true;
}

void setup() {
  Serial.begin(115200);
  
//  SPIFFS.remove("/refreshToken.txt");
//  SPIFFS.format();
//  File f = SPIFFS.open("/refreshToken.txt", "w+");
//  if (!f) Serial.println("Failed to open config file");
//  f.println("");
//  f.close();
//  delay(1000);
  
  boolean mounted = SPIFFS.begin();
  if (!mounted) {
    Serial.println("FS not formatted. Doing that now");
    SPIFFS.format();
    Serial.println("FS formatted...");
    SPIFFS.begin();
  }
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  String code = "";
  String grantType = "";
  String refreshToken = loadRefreshToken();
  if (refreshToken == "") {
    Serial.println("No refresh token found. Requesting through browser");
    Serial.println ( "Open browser at http://" + espotifierNodeName + ".local" );
    code = client.startConfigPortal();
    grantType = "authorization_code";
  } else {
    Serial.println("Using refresh token found on the FS");
    code = refreshToken;
    grantType = "refresh_token";
  }
  client.getToken(&auth, grantType, code);
  Serial.printf("Refresh token: %s\nAccess Token: %s\n", auth.refreshToken.c_str(), auth.accessToken.c_str());
  if (auth.refreshToken != "") {
    saveRefreshToken(auth.refreshToken);
  }

  touchAttachInterrupt(T0, gotTouch, threshold);
}

void loop() {
  if (millis() - lastUpdate > 1000) {
    uint16_t responseCode = client.update(&data, &auth);
//    Serial.printf("HREF: %s\n", data.image300Href.c_str());
    lastUpdate = millis();
    Serial.printf("--------Response Code: %d\n", responseCode);
//    Serial.printf("--------Free mem: %d\n", ESP.getFreeHeap());
    
    if (responseCode == 401) {
      client.getToken(&auth, "refresh_token", auth.refreshToken);
      if (auth.refreshToken != "") {
        saveRefreshToken(auth.refreshToken);
      }
    }
    
    if (responseCode == 200) {
      String selectedImageHref = data.image300Href;
      selectedImageHref.replace("https", "http");
      
      if (selectedImageHref != currentImageUrl) {
        currentImageUrl = selectedImageHref;
        Serial.println(currentImageUrl);
      }
    }
    
    if (responseCode == 400) {
      Serial.println("Please define clientId and clientSecret");
    }

    if (responseCode == 204) {
      Serial.println("Nothing is playing");
    }

  }
  
  if (touchDetected) {
    String method = "PUT"; 
    String command = "play";
    if (data.isPlaying) {
      command = "pause";
    }
    data.isPlaying = !data.isPlaying;   
    uint16_t responseCode = client.playerCommand(&auth, method, command);
    Serial.print("playerCommand response =");
    Serial.println(responseCode);
    touchDetected = false;
  }
}

void saveRefreshToken(String refreshToken) {
  Serial.println("Saving config");
  File f = SPIFFS.open("/refreshToken.txt", "w+");
  if (!f) {
    Serial.println("Failed to open config file");
    return;
  }
  f.println(refreshToken);
  f.close();
}

String loadRefreshToken() {
  Serial.println("Loading config");
  File f = SPIFFS.open("/refreshToken.txt", "r");
  if (!f) {
    Serial.println("Failed to open config file");
    return "";
  }
  while(f.available()) {
      //Lets read line by line from the file
      String token = f.readStringUntil('\r');
      Serial.printf("Refresh Token: %s\n", token.c_str());
      f.close();
      return token;
  }
  return "";
}
