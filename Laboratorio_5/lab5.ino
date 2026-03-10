// lee temperatura y humedad del sensor DHT22 y los muestra en el monitor serial cada 500 ms
#include <DHT.h>
#include <DHT_U.h>

#define PIN_SENSOR 2
#define TIPO_SENSOR DHT22

DHT sensor(PIN_SENSOR, TIPO_SENSOR);

// Función que imprime los datos
void mostrarDatos(float temperatura, float humedad)
{
    Serial.print("T=");
    Serial.print(temperatura);
    Serial.print(" C  |  H=");
    Serial.print(humedad);
    Serial.println(" %");
}

// Función que lee el sensor
bool leerSensor(float &temp, float &hum)
{
    temp = sensor.readTemperature();
    hum = sensor.readHumidity();

    if (isnan(temp) || isnan(hum))
    {
        return false;
    }
    return true;
}

void setup()
{
    Serial.begin(9600);
    sensor.begin();
}

void loop()
{

    float temperatura;
    float humedad;

    if (leerSensor(temperatura, humedad))
    {
        mostrarDatos(temperatura, humedad);
    }
    else
    {
        Serial.println("Error leyendo el sensor");
    }

    delay(500);
}