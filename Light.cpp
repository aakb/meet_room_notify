#include "Light.h"

#define PIN D1
#define NUMPIXELS 1

Light::Light() {
  this->pixels = new Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  this->pixels->begin();
}

void Light::on() {
  this->pixels->clear();

  for(int i=0; i<NUMPIXELS; i++) {
    this->pixels->setPixelColor(i, this->pixels->Color(150, 150, 0));
    this->pixels->show();
  }
}

void Light::off() {
  this->pixels->clear();
  this->pixels->show();
}
