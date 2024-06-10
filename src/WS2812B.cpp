#include "WS2812B.h"

WS2812B::WS2812B(uint16_t numPixels, uint8_t pin)
    : numPixels(numPixels), pin(pin)
{
    pixels = new uint8_t[numPixels * 3];
}

void WS2812B::begin()
{
    pinMode(pin, OUTPUT);
    clear();
}

void WS2812B::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    if (n >= numPixels)
        return;
    r = (r * brightness) / 255;
    g = (g * brightness) / 255;
    b = (b * brightness) / 255;
    pixels[n * 3] = g;
    pixels[n * 3 + 1] = r;
    pixels[n * 3 + 2] = b;
}

void WS2812B::show()
{
    noInterrupts();
    for (uint16_t i = 0; i < numPixels; i++)
    {
        sendPixel(pixels[i * 3], pixels[i * 3 + 1], pixels[i * 3 + 2]);
    }
    interrupts();
}

void WS2812B::clear()
{
    for (uint16_t i = 0; i < numPixels * 3; i++)
    {
        pixels[i] = 0;
    }
    show();
}

void WS2812B::sendPixel(uint8_t r, uint8_t g, uint8_t b)
{
    sendByte(g);
    sendByte(r);
    sendByte(b);
}

void WS2812B::sendBit(bool bitVal)
{
    if (bitVal)
    {
        digitalWrite(pin, HIGH);
        delayMicroseconds(0.8);
        digitalWrite(pin, LOW);
        delayMicroseconds(0.45);
    }
    else
    {
        digitalWrite(pin, HIGH);
        delayMicroseconds(0.4);
        digitalWrite(pin, LOW);
        delayMicroseconds(0.85);
    }
}

void WS2812B::sendByte(uint8_t byte)
{
    for (uint8_t bit = 0; bit < 8; bit++)
    {
        sendBit(byte & (1 << (7 - bit)));
    }
}

void WS2812B::red(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 255, 0, 0, brightness);
}

void WS2812B::green(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 0, 255, 0, brightness);
}

void WS2812B::blue(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 0, 0, 255, brightness);
}

void WS2812B::yellow(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 255, 255, 0, brightness);
}

void WS2812B::cyan(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 0, 255, 255, brightness);
}

void WS2812B::magenta(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 255, 0, 255, brightness);
}

void WS2812B::white(uint16_t n, uint8_t brightness)
{
    setPixelColor(n, 255, 255, 255, brightness);
}