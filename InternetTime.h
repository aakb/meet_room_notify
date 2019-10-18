#ifndef InternetTime_h
#define InternetTime_h

#include <NTPClient.h>
#include <WiFiUdp.h>

class InternetTime {
  public:
    // Constructor(s)
    InternetTime();
  
    String getFormattedTime();
    int getTimestamp();

  private:
    const long utcOffsetInSeconds = 0;
    NTPClient* timeClient;
};

#endif
