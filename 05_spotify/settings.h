// WiFi settings
const char* ssid = "[redacted]";
const char* password = "[redacted]";

// Spotify settings
String clientId = "[redacted]";
String clientSecret = "[redacted]";
// These next two lines have to match. A client clientSpotifierHostName makes the
// node listen on http://esp8266.local. Spotify needs an exact match of the redirect url
String espotifierNodeName = "192.168.0.44";
String redirectUri = "http%3A%2F%2F" + espotifierNodeName + "%2Fcallback%2F";
