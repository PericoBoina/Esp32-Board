#include <Arduino.h>

#include <WS2812.h>

#define LED_PIN 48  
#define NUM_LEDS 1 

WS2812 Neo(LED_PIN, NUM_LEDS);

void setup()
{
    Neo.begin();
}

void loop()
{
    for (int i = 0; i <= 255; i++)
    {
        Neo.setColor(0, i, 0, 0);
        Neo.show();
        delay(25);
    }
    Neo.Black(0);
    Neo.show();
    delay(25);
}
