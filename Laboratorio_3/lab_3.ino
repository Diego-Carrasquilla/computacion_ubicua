//led controlado por potenciómetro
int pinLED = 3; 

int pinPOT = A0; 


void setup() { 

  pinMode(pinLED, OUTPUT); 

} 


void loop() { 

  int valor = analogRead(pinPOT); // Lee el valor del potenciómetro (0 a 1023) 

  int PWM = map(valor, 0, 1023, 0, 255); // Mapea a rango PWM 

  analogWrite(pinLED, PWM); // Ajusta brillo vía PWM 

  delay(10); // Pequeña pausa 

}