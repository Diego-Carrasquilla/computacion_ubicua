#include <Bonezegei_DHT11.h>

// I2C
#include <Wire.h>

// LCD
#include <LiquidCrystal_I2C.h>

// DHT11 en pin 8
Bonezegei_DHT11 dht(8);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LM35
int pinLM35 = A0;

void setup()
{

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("hola profe");
    delay(2000);
    lcd.clear();
}

void loop()
{

    // ===== LM35 =====
    int valor = analogRead(pinLM35);
    float voltaje = valor * (5.0 / 1023.0);
    float tempLM35 = voltaje * 100;

    // ===== DHT11 =====
    float tempDHT = 0;
    float humedad = 0;

    if (dht.getData())
    {
        tempDHT = dht.getTemperature();
        humedad = dht.getHumidity();
    }
    else
    {
        tempDHT = -99;
        humedad = -1;
    }

    // ===== SERIAL =====
    Serial.print("LM35: ");
    Serial.print(tempLM35);
    Serial.print(" C | DHT11: ");

    if (tempDHT != -99)
    {
        Serial.print(tempDHT);
        Serial.print(" C | Humedad: ");
        Serial.print(humedad);
        Serial.print(" %");
    }
    else
    {
        Serial.print("Error");
    }
    Serial.println();

    // ===== LCD =====
    lcd.clear();

    // Línea 1 → DHT11
    lcd.setCursor(0, 0);
    if (tempDHT != -99)
    {
        lcd.print("T:");
        lcd.print(tempDHT);
        lcd.print("C H:");
        lcd.print(humedad);
        lcd.print("%");
    }
    else
    {
        lcd.print("Error DHT11");
    }

    // Línea 2 → LM35
    lcd.setCursor(0, 1);
    lcd.print("LM35:");
    lcd.print(tempLM35);
    lcd.print("C");

    delay(2000);
}