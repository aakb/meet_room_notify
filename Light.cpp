#include "Light.h"

#define PIN D1
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void Light::begin() {
  pixels.begin();
}

void Light::on() {
  pixels.clear();

  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 150, 0));
    pixels.show();
  }
}

void Light::off() {
  pixels.clear();
}