#ifndef FeedReader_h
#define FeedReader_h

#include <NTPClient.h>

#include <WiFiClientSecure.h>

class FeedReader {
  public:
  
    void begin();
    const long utcOffsetInSeconds = 3600;
};

#endif