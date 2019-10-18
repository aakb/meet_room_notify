#include "InternetTime.h"

WiFiUDP ntpUDP;

/**
 * Constructor.
 */
InternetTime::InternetTime() {
    this->timeClient = new NTPClient(ntpUDP, "0.dk.pool.ntp.org", this->utcOffsetInSeconds, 60000);
    this->timeClient->begin();
}

String InternetTime::getFormattedTime() {
  this->timeClient->update();
  return this->timeClient->getFormattedTime();
}

int InternetTime::getTimestamp() {
  this->timeClient->update();
  return this->timeClient->getEpochTime();
}
