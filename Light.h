#ifndef Light_h
#define Light_h

#include <Adafruit_NeoPixel.h>

class Light {
  public:
    Adafruit_NeoPixel* pixels;
  
    Light();
    
    void on();
    void off();
};

#endif
