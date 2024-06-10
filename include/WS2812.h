#ifndef WS2812_H
#define WS2812_H

#include <Arduino.h>
#include <driver/rmt.h>

class WS2812 {
public:
    WS2812(uint8_t pin, uint16_t numPixels);
    void begin();
    void setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void show();
// ----- Predefined colors ----- //
    void Red(uint16_t n);
    void Green(uint16_t n);
    void Blue(uint16_t n);
    void Yellow(uint16_t n);
    void Cyan(uint16_t n);
    void Magenta(uint16_t n);
    void White(uint16_t n);
    void Black(uint16_t n);
    void Orange(uint16_t n);
    void Purple(uint16_t n);

private:
    uint8_t _pin;
    uint16_t _numPixels;
    rmt_config_t _config;
    rmt_item32_t* _items;
    void rgbToRmt(uint8_t r, uint8_t g, uint8_t b, rmt_item32_t* items);
};

#endif
