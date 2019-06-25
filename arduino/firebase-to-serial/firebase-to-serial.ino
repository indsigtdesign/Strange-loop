#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6 // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1500 // Popular NeoPixel ring size
int numStars = 50;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int starsLit;
int star[150];
int starColor[150];
int dimStep = 5;
int first;
int last;

int startLed = 0;
int endLed = 0;

String inData = "";
bool isSetup = false;
bool twinkleBreak = true;

void setup() {
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.setBrightness(50);
  pixels.show();
  generateStars(1, NUMPIXELS);
}

void loop() {

  if (!isSetup || twinkleBreak) {
    twinkle(150, 151);
  } else {
    guideTheWay(startLed, endLed);
  }

  while (Serial.available() > 0) {

    char received = Serial.read();
    inData.concat(received);

    // Process message when new line character is received
    if (received == '\n') {
      Serial.println(inData);
      if (!isSetup && inData.toInt() == 9) {
        isSetup = true;
        Serial.println("ready");
      } if (inData.toInt() == 99) {
        twinkleBreak = false;
      } if (inData.toInt() == 999) {
        twinkleBreak = true;
      } else {
        int commaIndex = inData.indexOf(',');
        //  Search for the next comma just after the first
        int secondCommaIndex = inData.indexOf(',', commaIndex + 1);

        String firstValue = inData.substring(0, commaIndex);
        String secondValue = inData.substring(commaIndex + 1, secondCommaIndex);

        startLed = firstValue.toInt();
        endLed = secondValue.toInt();
      }
      inData = "";
    }
  }
}

void guideTheWay(int first_, int last_) {
  int dimmer;
  int total = last_ - first_;
  for (int i = 0; i < total; i++) {
    twinkle(first_, last_);
    pixels.setPixelColor(first_ + i, dimmer, dimmer, dimmer);
    dimmer = dimmer + 2;
    pixels.show();
  }

  for (int i = 0; i < last_; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
  pixels.show();
}

void generateStars(int first_, int last_) {
  first = first_;
  last = last_;
  numStars = (last - first) / 20;

  for (int i = 0; i < numStars; i++) {
    int pixel = random(first, last);
    int color = random(0, 255);
    pixels.setPixelColor(pixel, color, color, color);
    star[i] = pixel;
    starColor[i] = color;
    pixels.show();
  }
  starsLit = numStars;
}

void twinkle(int first_, int last_) {
  for (int e = 0; e < numStars; e++) {
    if (star[e] > last_ || star[e] < first_) {
      if (starColor[e] > dimStep) {
        int color = starColor[e] - dimStep;
        pixels.setPixelColor(star[e], color, color, color);
        starColor[e] = color;
      }
    } else {
      addStar(e);
    }

    if (starColor[e] <= dimStep) {
      pixels.setPixelColor(star[e], 0, 0, 0);
      addStar(e);
    }
  }
  pixels.show();
}

void addStar(int newPixel) {
  int pixel = random(first, last);
  int color = random(0, 255);
  star[newPixel] = pixel;
  starColor[newPixel] = color;
}
