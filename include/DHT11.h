#ifndef DHT11_h
#define DHT11_h

#include "Arduino.h"

class DHT11
{
public:
  DHT11(int pin);
  void setDelay(unsigned long delay);
  int readHumidity();
  int readTemperature();
  int readTemperatureHumidity(int &temperature, int &humidity);
  static const int ERROR_CHECKSUM = 254;
  static const int ERROR_TIMEOUT = 253;
  static const int TIMEOUT_DURATION = 1000;
  static String getErrorString(int errorCode);

private:
  int _pin;
  unsigned long _delayMS = 500;
  int readRawData(byte data[5]);
  byte readByte();
  void startSignal();
};

#endif
