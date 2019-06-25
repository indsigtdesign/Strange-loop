#include <FastLED.h>
#include "Messenger.h"

#define DATA_PIN    6
#define NUM_LEDS    300
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

int wait = 10;

void setup() {
  delay(3000); // 3 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  goToStation(1);
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
