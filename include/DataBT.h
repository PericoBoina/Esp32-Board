#ifndef DATABT_H
#define DATABT_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class DataBT
{
public:
    DataBT();
    void begin();
    void update();
    int getR() const;
    int getG() const;
    int getB() const;

private:
    BluetoothSerial SerialBT;
    int R, G, B;
    void parseData(String data);
};

#endif
