#include <Arduino.h>
#include <WS2812.h>
#include <DataBT.h>

#define LED_PIN 48
#define NUM_LEDS 1

WS2812 Neo(LED_PIN, NUM_LEDS);

void setup()
{
    Neo.begin();
}

void loop()
{
    Neo.Orange(0);
    Neo.show();
    delay(250);
    Neo.Black(0);
    Neo.show();
    delay(250);
}
