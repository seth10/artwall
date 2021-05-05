// Call up the SPIFFS FLASH filing system this is part of the ESP Core
#define FS_NO_GLOBALS
#include <FS.h>

#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif

// JPEG decoder library
#include <JPEGDecoder.h>

#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

/* Duplicate frames
 * 001: 13
 * 014: 2
 * 016: 2
 * 018: 2
 * 020: 2
 * 023: 77
 * 099: 2
 * 102: 5
 * 107: 3
 * 110: 13
 * 123: 2
 * 125: 2
 * 129: 3
 * 132: 3
 * 136: 5
 * 141: 2
 * 143: 3
 * 146: 3
 * ...
 */

void setup()
{
  Serial.begin(115200);

  delay(10);
  Serial.println("NodeMCU decoder test!");

  tft.begin();
  tft.setRotation(1);  // 0 & 2 Portrait. 1 & 3 landscape
  //tft.fillScreen(TFT_BLACK);

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nInitialisation done.");
  listFiles(); // Lists the files so you can see what is in the SPIFFS
}

void loop()
{
  char filename[9];
  for (int i = 0; i < 428; i+=2) { // started skipping frames to speed up animation
    sprintf(filename, "/%03d.jpg", i);
    drawJpeg(filename, 0 , 0);   
  }
}
