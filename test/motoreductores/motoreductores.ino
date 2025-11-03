/*
EJERCICIO
Haz un algoritmo de movimiento para que el auto avance en zig zag 3 veces, luego pare y espere 2 segundos y comience de nuevo

Pista: haz un plan y ejecutalo en la función de loop()!
*/


// --- Pines del puente H L298N ---
const int motor1Pin1 = 2;   // IN1
const int motor1Pin2 = 4;   // IN2
const int motor2Pin1 = 32;  // IN3
const int motor2Pin2 = 33;  // IN4

// --- Pines de habilitación (Velocidad PWM) ---
const int enableAPin = 25;  // ENA (para Motor 1)
const int enableBPin = 26;  // ENB (para Motor 2)

// --- Configuración del PWM (LED Control) para el ESP32 ---
const int freq = 5000;      // Frecuencia de 5kHz para el PWM
const int resolution = 8;   // Resolución de 8 bits (0-255)

// Canales PWM (puedes usar del 0 al 15)
const int channelA = 0;     // Canal PWM para Motor A
const int channelB = 1;     // Canal PWM para Motor B

// Velocidad (0 = detenido, 255 = máximo)
const int velocidad = 200;  // Usemos un valor un poco menor que el máximo para probar

void setup() {
  // Configurar pines de dirección como SALIDA
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // --- Configuración PWM para el ESP32 ---
  // 1. Configurar los canales PWM
  ledcSetup(channelA, freq, resolution);
  ledcSetup(channelB, freq, resolution);

  // 2. Asociar los pines ENA y ENB a sus canales PWM
  ledcAttachPin(enableAPin, channelA);
  ledcAttachPin(enableBPin, channelB);

  // Iniciar la comunicación serial para depuración
  Serial.begin(115200); // Es mejor usar 115200 con el ESP32
  Serial.println("Prueba de motores iniciada...");
}

void loop() {
  
  Serial.println("Avanzando...");
  avanzar();
  delay(1000); // Avanza por 1 segundo

  Serial.println("Deteniendo...");
  detener();
  delay(500); // Pausa

  Serial.println("Girando Izquierda...");
  girarIzquierda();
  delay(1000); 

  Serial.println("Deteniendo...");
  detener();
  delay(500); 

  Serial.println("Girando Derecha...");
  girarDerecha();
  delay(1000);

  Serial.println("Deteniendo...");
  detener();
  delay(500);

  Serial.println("Retrocediendo...");
  retroceder();
  delay(1000); 

  Serial.println("Deteniendo...");
  detener();
  delay(2000); // Pausa más larga antes de repetir
}

// --- Funciones de Movimiento ---

void avanzar() {
  // Motor 1: Adelante
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  // Motor 2: Adelante
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  // Establecer velocidad
  ledcWrite(channelA, velocidad);
  ledcWrite(channelB, velocidad);
}

void retroceder() {
  // Motor 1: Reversa
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  // Motor 2: Reversa
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  // Establecer velocidad
  ledcWrite(channelA, velocidad);
  ledcWrite(channelB, velocidad);
}

void girarIzquierda() {
  // Motor 1: Reversa (o detenido)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  // Motor 2: Adelante
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  // Establecer velocidad
  ledcWrite(channelA, velocidad);
  ledcWrite(channelB, velocidad);
}

void girarDerecha() {
  // Motor 1: Adelante
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  // Motor 2: Reversa (o detenido)
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  // Establecer velocidad
  ledcWrite(channelA, velocidad);
  ledcWrite(channelB, velocidad);
}

void detener() {
  // Poner ambos pines de un motor en LOW (o HIGH) lo frena
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

  // También puedes poner la velocidad a 0
  ledcWrite(channelA, 0);
  ledcWrite(channelB, 0);
}