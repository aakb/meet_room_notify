
// WifiConfiguraion.
#include "WifiSetup.h"

#include "Config.h"
Config config;

#include "Light.h"
Light light;

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

  // Stop led flashing.
  ticker.detach();
}

void loop() {

}
