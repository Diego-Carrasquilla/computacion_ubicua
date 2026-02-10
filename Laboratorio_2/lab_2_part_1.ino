// El led se enciende cuando el pulsador esta presionado y se apaga cuando el pulsador no esta presionado
void setup() {
    pinMode(2, INPUT);     // pin 2 como entrada 
    pinMode(3, OUTPUT);    // pin 3 como salido
  
  }
  
  void loop() {
    if (digitalRead(2) == HIGH) {   // evaluo si la entrada esta a nivel alto
      digitalWrite(3, HIGH);        // enciendo LED
    }
    else {
      digitalWrite(3, LOW);         // apago LED
    }
  }