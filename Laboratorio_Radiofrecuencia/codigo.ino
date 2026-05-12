// --- Motor Shield L298P ---
// Motor A conectado a M1 (izquierdo)
// Motor B conectado a M2 (derecho)

// Pines Motor A
#define IN1 12
#define IN2 13
#define ENA 10

// Pines Motor B
#define IN3 8
#define IN4 9
#define ENB 11

// Pines receptor KRF100
#define D0 2 // Botón adelante
#define D1 3 // Botón atrás
#define D2 4 // Botón izquierda
#define D3 5 // Botón derecha

// --- Compensación de potencia ---
#define COMP_IZQ 10 // Pequeña corrección si el A es más débil
#define COMP_DER 10 // Igualamos los dos motores

// --- VELOCIDAD BASE ---
// Máximo 255 → potencia total
#define VELOCIDAD_BASE 240 // Más potencia general

void setup()
{
    Serial.begin(9600);

    // Configurar pines del motor
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Configurar pines del receptor
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);

    Serial.println("Sistema listo...");
}

void loop()
{
    // Leer señales del control remoto
    bool adelante = digitalRead(D0);
    bool atras = digitalRead(D1);
    bool izquierda = digitalRead(D2);
    bool derecha = digitalRead(D3);

    // --- Control lógico ---
    if (adelante)
    {
        Adelante();
    }
    else if (atras)
    {
        Atras();
    }
    else if (izquierda)
    {
        Izquierda();
    }
    else if (derecha)
    {
        Derecha();
    }
    else
    {
        Parar();
    }
}

// --- FUNCIONES DE MOVIMIENTO ---

void Adelante()
{
    Serial.println("→ Adelante");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, limitar(VELOCIDAD_BASE + COMP_IZQ));

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, limitar(VELOCIDAD_BASE + COMP_DER));
}

void Atras()
{
    Serial.println("← Atrás");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, limitar(VELOCIDAD_BASE + COMP_IZQ));

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, limitar(VELOCIDAD_BASE + COMP_DER));
}

void Izquierda()
{
    Serial.println("↺ Izquierda");
    // Motor izquierdo detenido
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);

    // Motor derecho adelante
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, limitar(VELOCIDAD_BASE + COMP_DER));
}

void Derecha()
{
    Serial.println("↻ Derecha");
    // Motor izquierdo adelante
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, limitar(VELOCIDAD_BASE + COMP_IZQ));

    // Motor derecho detenido
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
}

void Parar()
{
    Serial.println("■ Parado");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}

// --- Función de seguridad para no pasar de 255 ---
int limitar(int valor)
{
    if (valor > 255)
        return 255;
    if (valor < 0)
        return 0;
    return valor;
}