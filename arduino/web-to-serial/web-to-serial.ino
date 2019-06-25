#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

int wait = 10;

String inData = "";
bool isSetup = false;

void setup() {
  delay(3000); // 3 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
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
      goToStation(inData.toInt());
      inData = "";
    }
  }
}

void goToStation(int pos){
  for (int dot = 0; dot < NUM_LEDS/pos; dot++) {
    leds[dot].setRGB(255,255,255);
    FastLED.show();
    delay(wait);
  }
  
  for (int dot = 0; dot < NUM_LEDS/pos; dot++) {
      leds[dot+4].setRGB(204,204,204);
      leds[dot+3].setRGB(153,153,153);
      leds[dot+2].setRGB(102,102,102);
      leds[dot+1].setRGB(51,51,51);
      leds[dot+0].setRGB(0,0,0);
      FastLED.show();
      delay(wait);
  }
}
