#include "WifiSetup.h"

// Static variable used to set config state.
bool WifiSetup::shouldSaveConfig = false;

/**
 * Constructor.
 */
WifiSetup::WifiSetup(servConfig config) {
    WifiSetup::shouldSaveConfig = false;

    this->config = config;
}

/**
 * Get state for configuration. 
 */
bool WifiSetup::hasConfigChanged() {
  return WifiSetup::shouldSaveConfig;
}

/**
 * Get local ip.
 */
IPAddress WifiSetup::getIp() {
  return WiFi.localIP();
}

/**
 * Static method to use to change config state.
 */
void WifiSetup::saveConfigCallback () {
  Serial.println("Should save config");
  WifiSetup::shouldSaveConfig = true;
}

/**
 * Get current configuration.
 */
servConfig WifiSetup::getConfig() {
  return this->config;
}

/**
 * Start WifiMangner and connect to the network.
 * 
 * Network connection errors table.
 * 
 * WL_IDLE_STATUS      = 0
 * WL_NO_SSID_AVAIL    = 1
 * WL_SCAN_COMPLETED   = 2
 * WL_CONNECTED        = 3
 * WL_CONNECT_FAILED   = 4
 * WL_CONNECTION_LOST  = 5
 * WL_DISCONNECTED     = 6 
 */
void WifiSetup::begin() {
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  WiFiManagerParameter custom_apikey("apikey", "API-KEY", this->config.apikey, 40);
  WiFiManagerParameter custom_addr("addr", "FQDN", this->config.addr, 256);
  WiFiManagerParameter custom_fingerprint("fingerprint", "SSL fingerprint", this->config.fingerprint, 60);
  WiFiManagerParameter custom_interval("interval", "Interval", String(this->config.interval).c_str(), 10);

  // Reset settings - for testing
  //wifiManager.resetSettings();

  // Disable default serial debug output.
  //wifiManager.setDebugOutput(false);

  // set config save notify callback
  wifiManager.setSaveConfigCallback(WifiSetup::saveConfigCallback);
 
  // Add all your parameters here.
  wifiManager.addParameter(&custom_apikey);
  wifiManager.addParameter(&custom_addr);
  wifiManager.addParameter(&custom_fingerprint);
  wifiManager.addParameter(&custom_interval);

  if (!wifiManager.autoConnect("MeetRoom", "password")) {
    Serial.println("Failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  if (WifiSetup::shouldSaveConfig) {
    strncpy(this->config.apikey, custom_apikey.getValue(), sizeof(this->config.apikey)/sizeof(char));
    strncpy(this->config.addr, custom_addr.getValue(), sizeof(this->config.addr)/sizeof(char));
    strncpy(this->config.fingerprint, custom_fingerprint.getValue(), sizeof(this->config.fingerprint)/sizeof(char));
    this->config.interval = atoi(custom_interval.getValue());

    Serial.println("---------------------===---------------------");
    Serial.println(this->config.apikey);
    Serial.println(this->config.addr);
    Serial.println(this->config.fingerprint);
    Serial.println(this->config.interval);
    Serial.println("---------------------===---------------------");
  }
}
