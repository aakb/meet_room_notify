#include <Adafruit_NeoPixel.h>

// WifiConfiguraion.
#include "WifiSetup.h"

#include "Config.h"
Config config;

// LED status.
#include <Ticker.h>
Ticker ticker;

/**
 * Ticker callback that change led (flip on/off).
 */
void tick() {
  int state = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, !state);
}

/*********-------------------------**********/

#define PIN D1
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  // Set led pin as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Flash the led.
  ticker.attach(1, tick);

  // Load configuration.
  if (!config.load()) {
    // Set defaults.
    Serial.println("No config");
  }
  else {
    Serial.println("Config loaded");
  }

  // Start wifi manager.
  WifiSetup* wifiSetup = new WifiSetup(config.config);
  wifiSetup->begin();

  if (wifiSetup->hasConfigChanged()) {
    // Save configuration.
    config.config = wifiSetup->getConfig();
    config.save();
  }
  delay(5000);

  randomSeed(micros());
  
  Serial.print("local ip: ");
  String ip =  wifiSetup->getIp().toString();
  Serial.println(ip);

  pixels.begin();

  // Stop led flashing.
  ticker.detach();
}

void loop() {
 pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(150, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(100000); // Pause before next pass through loop
  }
}
