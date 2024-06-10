#include "WS2812.h"

WS2812::WS2812(uint8_t pin, uint16_t numPixels)
    : _pin(pin), _numPixels(numPixels) {
    _config.rmt_mode = RMT_MODE_TX;
    _config.channel = RMT_CHANNEL_0;
    _config.gpio_num = (gpio_num_t)pin;
    _config.mem_block_num = 1;
    _config.tx_config.loop_en = false;
    _config.tx_config.carrier_en = false;
    _config.tx_config.idle_output_en = true;
    _config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
    _config.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
    _config.clk_div = 2; // Divisor de reloj para 40MHz (1 tick = 25ns)

    _items = (rmt_item32_t*)malloc(numPixels * 24 * sizeof(rmt_item32_t) + 1 * sizeof(rmt_item32_t));
}

void WS2812::begin() {
    rmt_config(&_config);
    rmt_driver_install(_config.channel, 0, 0);
}

void WS2812::setColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
    if (n >= _numPixels) return;
    rgbToRmt(r, g, b, &_items[n * 24]);
}

void WS2812::show() {
    // Añadir un item adicional para el reset
    _items[_numPixels * 24].duration0 = 2000; // 50us para reset
    _items[_numPixels * 24].level0 = 0;
    _items[_numPixels * 24].duration1 = 2000;
    _items[_numPixels * 24].level1 = 0;

    rmt_write_items(_config.channel, _items, _numPixels * 24 + 1, true);
    rmt_wait_tx_done(_config.channel, portMAX_DELAY);
}

void WS2812::rgbToRmt(uint8_t r, uint8_t g, uint8_t b, rmt_item32_t* items) {
    uint32_t bits = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    for (int i = 23; i >= 0; i--) {
        if (bits & (1 << i)) {
            items[23 - i].duration0 = 28; // T1H = 700ns (28 ticks)
            items[23 - i].level0 = 1;
            items[23 - i].duration1 = 15; // T1L = 600ns (24 ticks)
            items[23 - i].level1 = 0;
        } else {
            items[23 - i].duration0 = 14; // T0H = 350ns (14 ticks)
            items[23 - i].level0 = 1;
            items[23 - i].duration1 = 32; // T0L = 800ns (32 ticks)
            items[23 - i].level1 = 0;
        }
    }
}

void WS2812::Red(uint16_t n) {
    setColor(n, 255, 0, 0);
}

void WS2812::Green(uint16_t n) {
    setColor(n, 0, 255, 0);
}

void WS2812::Blue(uint16_t n) {
    setColor(n, 0, 0, 255);
}

void WS2812::Yellow(uint16_t n) {
    setColor(n, 255, 255, 0);
}

void WS2812::Cyan(uint16_t n) {
    setColor(n, 0, 255, 255);
}

void WS2812::Magenta(uint16_t n) {
    setColor(n, 255, 0, 255);
}

void WS2812::White(uint16_t n) {
    setColor(n, 255, 255, 255);
}

void WS2812::Black(uint16_t n) {
    setColor(n, 0, 0, 0);
}

void WS2812::Orange(uint16_t n) {
    setColor(n, 255, 165, 0);
}

void WS2812::Purple(uint16_t n) {
    setColor(n, 128, 0, 128);
}
