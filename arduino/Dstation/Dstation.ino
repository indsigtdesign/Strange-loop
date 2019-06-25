#include <Adafruit_NeoPixel.h>

int wait = 10;

String inData = "";
bool isSetup = false;

int screenState = 0;

int ringOne[] = {13, 14, 15, 16, 17, 18, 19, 35, 34, 33, 32, 31};
int ringOneLength = 12;
int ringTwo[] = {0, 1, 2, 3, 4, 5, 6, 7, 30, 29, 28, 27};
int ringTwoLength = 12;
int theLoop[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
int theLoopLength = 27;
int bottomLine[] = {21, 22, 23, 24, 25, 26,};
int bottomLineLength = 6;
int topLine[] = {7, 8, 9, 10, 11, 12};
int topLineLength = 6;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN  6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 36

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  delay(1000); // 1 second delay for recovery
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  for (int dot = 0; dot < NUMPIXELS; dot++) {
    pixels.setPixelColor(dot, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void loop() {

  if (!isSetup) {
    isSetup = true;
    delay(2000);
    Serial.println("ready");
  }

  while (Serial.available() > 0) {
    char received = Serial.read();
    inData.concat(received);

    // Process message when new line character is received
    if (received == '\n') {
      Serial.println(inData);
      screenState = inData.toInt();
      inData = "";
    }
  }

  if (screenState == 3) {
    pixels.clear();
    for (int f = 0; f < 255; f++) {
      for (int e = 0; e < ringOneLength; e++) {
        pixels.setPixelColor(ringOne[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }

    for (int f = 255; f > 0; f--) {
      for (int e = 0; e < ringOneLength; e++) {
        pixels.setPixelColor(ringOne[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }
  }

  else if (screenState == 4) {
    pixels.clear();
    for (int f = 0; f < 255; f++) {
      for (int e = 0; e < ringTwoLength; e++) {
        pixels.setPixelColor(ringTwo[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }

    for (int f = 255; f > 0; f--) {
      for (int e = 0; e < ringTwoLength; e++) {
        pixels.setPixelColor(ringTwo[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }
  }

  else {
    pixels.clear();
    for (int f = 0; f < 255; f++) {
      for (int e = 0; e < theLoopLength; e++) {
        pixels.setPixelColor(theLoop[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }

    for (int f = 255; f > 0; f--) {
      for (int e = 0; e < theLoopLength; e++) {
        pixels.setPixelColor(theLoop[e], 0, 0, 0, f);
      }
      pixels.show();
      delay(wait);
    }
  }
  
}
