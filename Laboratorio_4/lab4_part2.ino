// sensor de temperatura muestra en pantalla los valores promedios cada 5 segundos
#include <LiquidCrystal.h>

#define PIN_SENSOR A0
#define NUM_MUESTRAS 5

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float leerLM35()
{
    int valor = analogRead(PIN_SENSOR);
    float voltaje = valor * (5000.0 / 1023.0);
    float temperatura = (voltaje / 10.0) - 50;
    return temperatura;
}

float calcularPromedio()
{
    float acumulador = 0;

    for (int i = 0; i < NUM_MUESTRAS; i++)
    {
        acumulador += leerLM35();
        delay(500);
    }

    return acumulador / NUM_MUESTRAS;
}

void mostrarTemperatura(float temp)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp promedio:");
    lcd.setCursor(0, 1);
    lcd.print(temp, 1);
    lcd.print(" C");
}

void setup()
{
    lcd.begin(16, 2);
}

void loop()
{
    float temperaturaPromedio = calcularPromedio();
    mostrarTemperatura(temperaturaPromedio);
}