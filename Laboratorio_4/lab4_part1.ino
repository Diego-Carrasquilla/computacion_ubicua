// sensor unicamente leyendo temperatura
#define PIN_TEMP A0
#define MUESTRAS 5

void setup()
{
    Serial.begin(9600);
}

float leerTemperatura()
{
    int valor = analogRead(PIN_TEMP);
    float voltaje = valor * (5000.0 / 1023.0);
    return voltaje / 10.0;
}

float obtenerPromedio()
{
    float total = 0;

    for (int i = 0; i < MUESTRAS; i++)
    {
        total += leerTemperatura();
        delay(500);
    }

    return total / MUESTRAS;
}

void loop()
{
    float promedio = obtenerPromedio();
    Serial.println(promedio, 1);
}