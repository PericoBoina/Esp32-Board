#include "DHT11.h"

DHT11::DHT11(int pin) : _pin(pin)
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

void DHT11::setDelay(unsigned long delay)
{
  _delayMS = delay;
}
int DHT11::readRawData(byte data[5])
{
  delay(_delayMS);
  startSignal();
  unsigned long timeout_start = millis();
  while (digitalRead(_pin) == HIGH)
  {
    if (millis() - timeout_start > TIMEOUT_DURATION)
    {
      return DHT11::ERROR_TIMEOUT;
    }
  }
  if (digitalRead(_pin) == LOW)
  {
    delayMicroseconds(80);
    if (digitalRead(_pin) == HIGH)
    {
      delayMicroseconds(80);
      for (int i = 0; i < 5; i++)
      {
        data[i] = readByte();
        if (data[i] == DHT11::ERROR_TIMEOUT)
        {
          return DHT11::ERROR_TIMEOUT;
        }
      }
      if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
      {
        return 0; // Success
      }
      else
      {
        return DHT11::ERROR_CHECKSUM;
      }
    }
  }
  return DHT11::ERROR_TIMEOUT;
}

byte DHT11::readByte()
{
  byte value = 0;

  for (int i = 0; i < 8; i++)
  {
    while (digitalRead(_pin) == LOW)
      ;
    delayMicroseconds(30);
    if (digitalRead(_pin) == HIGH)
    {
      value |= (1 << (7 - i));
    }
    while (digitalRead(_pin) == HIGH)
      ;
  }
  return value;
}

void DHT11::startSignal()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(18);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);
}

int DHT11::readTemperature()
{
  byte data[5];
  int error = readRawData(data);
  if (error != 0)
  {
    return error;
  }
  return data[2];
}

int DHT11::readHumidity()
{
  byte data[5];
  int error = readRawData(data);
  if (error != 0)
  {
    return error;
  }
  return data[0];
}

int DHT11::readTemperatureHumidity(int &temperature, int &humidity)
{
  byte data[5];
  int error = readRawData(data);
  if (error != 0)
  {
    return error;
  }
  humidity = data[0];
  temperature = data[2];
  return 0;
}

String DHT11::getErrorString(int errorCode)
{
  switch (errorCode)
  {
  case DHT11::ERROR_TIMEOUT:
    return "Error 253 Reading from DHT11 timed out.";
  case DHT11::ERROR_CHECKSUM:
    return "Error 254 Checksum mismatch while reading from DHT11.";
  default:
    return "Error Unknown.";
  }
}
