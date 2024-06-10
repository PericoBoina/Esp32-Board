#include <Arduino.h>
#include <LSM6DS3.h>
#include <DHT11.h>
#include <WS2812B.h>
#include <SPI.h>
#include <SD.h>

#define SD_MOSI 17
#define SD_MISO 16
#define SD_SCK  19
#define SD_CS   18

SPIClass mySPI(VSPI);

void setup()
{
    Serial.begin(115200);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH); // Desactiva la tarjeta SD para comenzar

    if (!SD.begin(SD_CS, mySPI, SD_MISO, SD_MOSI, SD_SCK, "/mySD"))
    {
        Serial.println("Error al inicializar la tarjeta SD.");
        return;
    }

    Serial.println("Tarjeta SD lista.");
}

void loop()
{
}
