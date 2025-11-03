#define pinLed 4

void setup() {
  Serial.begin(115200);
  
  pinMode(pinLed, OUTPUT);
}





void loop() {
  // Tip: HIGH = 1 o Verdadero  y  LOW = 0 o Falso
  digitalWrite(pinLed, HIGH);
  Serial.println("Encender flash");
  delay(1000); // milisegundos, 1000 = 1 segundo

  // Ejercicio: Encender la led, y luego de 1 segundo que se apague
}
