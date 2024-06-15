#include "DataBT.h"

DataBT::DataBT() : R(0), G(0), B(0){
}

void DataBT::begin()
{
 SerialBT.begin("ESP32Board");
}

void DataBT::update()
{
    if (SerialBT.available())
    {
        String data = SerialBT.readStringUntil('\n');
        parseData(data);
        }
}

void DataBT::parseData(String data) {
    int idx1 = data.indexOf(',');
    int idx2 = data.indexOf(',', idx1 + 1);
    int idx3 = data.indexOf(',', idx2 + 1);
    
    if (idx1 == -1 || idx2 == -1 || idx3 == -1)
        return;
    R = data.substring(0, idx1).toFloat();
    G = data.substring(idx1 + 1, idx2).toFloat();
    B = data.substring(idx2 + 1, idx3).toFloat();
}

int DataBT::getR() const {
    return R;
}

int DataBT::getG() const {
    return G;
}

int DataBT::getB() const {
    return B;
}
