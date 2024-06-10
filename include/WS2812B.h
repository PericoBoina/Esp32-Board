#ifndef WS2812B_H
#define WS2812B_H
#include "Arduino.h"

class WS2812B
{
public:
    WS2812B(uint16_t numPixels, uint8_t pin);
    void begin();
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness = 255);
    void show();
    void clear();

    // ---- Colores Definidos ---- //

    void red(uint16_t n, uint8_t brightness = 255);
    void green(uint16_t n, uint8_t brightness = 255);
    void blue(uint16_t n, uint8_t brightness = 255);
    void yellow(uint16_t n, uint8_t brightness = 255);
    void cyan(uint16_t n, uint8_t brightness = 255);
    void magenta(uint16_t n, uint8_t brightness = 255);
    void white(uint16_t n, uint8_t brightness = 255);

private:
    uint16_t numPixels;
    uint8_t pin;
    uint8_t *pixels;
    void sendPixel(uint8_t r, uint8_t g, uint8_t b);
    void sendBit(bool bitVal);
    void sendByte(uint8_t byte);
};

#endif
