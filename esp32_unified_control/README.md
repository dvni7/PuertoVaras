# ESP32 Unified Control System

Sistema de control unificado para ESP32 que integra todas las funcionalidades de prueba en un único programa con interfaz web.

## 🎯 Características

Este código unifica y permite controlar:

1. **💡 LED Flash** - Control de encendido/apagado del LED integrado
2. **🚗 Motores DC** - Control de dirección y velocidad de motores con puente H L298N
3. **🎚️ Servo Motor** - Control de posición del servo (0-180°)
4. **📹 Cámara Web** - Streaming de video en tiempo real desde la ESP32-CAM

## 🔧 Hardware Requerido

- **ESP32-CAM** (modelo AI-THINKER con PSRAM)
- **Puente H L298N** para control de motores DC
- **2 Motores DC** con reductores
- **Servo Motor** (tipo SG90 o similar)
- **LED** (integrado en pin 4 o externo)
- **Fuente de alimentación** adecuada para motores (recomendado 7-12V)

## 📌 Conexiones de Pines

### LED
- **Pin 4** - LED Flash (integrado en ESP32-CAM)

### Motores DC (Puente H L298N)
- **Pin 2** - Motor 1, IN1
- **Pin 4** - Motor 1, IN2 (⚠️ compartido con LED, ajustar si hay conflicto)
- **Pin 32** - Motor 2, IN3
- **Pin 33** - Motor 2, IN4
- **Pin 25** - ENA (PWM para velocidad Motor A)
- **Pin 26** - ENB (PWM para velocidad Motor B)

### Servo Motor
- **Pin 13** - Señal de control del servo

### Cámara
Los pines de la cámara están predefinidos para el modelo AI-THINKER en `camera_pins.h`

## 📚 Librerías Necesarias

Instala estas librerías desde el Administrador de Librerías de Arduino IDE:

1. **ESP32Servo** by Kevin Harrington
   - Menú → Herramientas → Administrar Bibliotecas
   - Buscar "ESP32Servo" e instalar

2. **esp32** board package
   - Archivo → Preferencias
   - URLs adicionales de gestor de tarjetas:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Herramientas → Placa → Gestor de tarjetas
   - Buscar "esp32" e instalar

## 🚀 Instrucciones de Uso

### 1. Configuración en Arduino IDE

1. **Seleccionar la placa correcta:**
   - Herramientas → Placa → ESP32 Arduino → AI Thinker ESP32-CAM

2. **Configurar el esquema de partición:**
   - Herramientas → Partition Scheme → Huge APP (3MB No OTA/1MB SPIFFS)
   - Esto es importante para que quepa el código con la cámara

3. **Configurar PSRAM:**
   - Herramientas → PSRAM → Enabled

4. **Puerto serie:**
   - Conecta el programador FTDI o USB-TTL
   - Selecciona el puerto COM correcto en Herramientas → Puerto

### 2. Subir el Código

1. Abre el archivo `esp32_unified_control.ino`
2. Ajusta las credenciales WiFi si deseas (líneas 24-25):
   ```cpp
   const char* ap_ssid = "ESP32-Control";
   const char* ap_password = "12345678";
   ```
3. Verifica y sube el código al ESP32
4. Abre el Monitor Serie (115200 baud) para ver el estado

### 3. Conectarse al ESP32

1. **Busca la red WiFi** creada por el ESP32:
   - SSID: `ESP32-Control`
   - Password: `12345678`

2. Conéctate a esa red desde tu celular, tablet o PC

3. **Abre el navegador web** y ve a:
   ```
   http://192.168.4.1
   ```

4. ¡Verás la interfaz de control!

## 🎮 Uso de la Interfaz Web

### 💡 Control de LED
- **Encender LED** - Enciende el LED flash
- **Apagar LED** - Apaga el LED flash
- Indicador visual muestra el estado actual

### 🚗 Control de Motores
- **⬆️ Avanzar** - Mueve ambos motores hacia adelante
- **⬇️ Retroceder** - Mueve ambos motores hacia atrás
- **⬅️ Girar Izq.** - Gira el robot a la izquierda
- **➡️ Girar Der.** - Gira el robot a la derecha
- **⏹️ Detener** - Detiene todos los motores
- **Slider de Velocidad** - Ajusta la velocidad (0-255)

### 🎚️ Control de Servo
- **Slider** - Mueve el servo de 0° a 180°
- **Botones rápidos** - Posiciones predefinidas (0°, 90°, 180°)
- Display muestra la posición actual en grados

### 📹 Cámara en Vivo
- El streaming de video se muestra automáticamente
- Si la cámara no está disponible, verás un mensaje de error

## ⚠️ Notas Importantes

### Conflicto de Pines
El **Pin 4** está configurado tanto para el LED como para uno de los pines del motor (IN2). Si esto causa problemas:

**Opción 1:** Usar solo LED O motores, no ambos simultáneamente
**Opción 2:** Cambiar el pin del motor IN2 a otro pin disponible:
```cpp
const int motor1Pin2 = 15;  // Cambiar a pin 15, por ejemplo
```

### Alimentación
- Los motores DC requieren **alimentación externa** (no usar USB)
- Conecta una batería o fuente de 7-12V al L298N
- Asegúrate de conectar los GND comunes (ESP32 y L298N)

### Memoria
- Si el código no cabe, asegúrate de tener seleccionado el partition scheme correcto
- Si no usas la cámara, puedes comentar el código relacionado para liberar memoria

### Rango del WiFi
- La ESP32 en modo AP tiene un rango limitado (10-30 metros típicamente)
- Mantén el dispositivo que se conecta cerca del ESP32

## 🐛 Solución de Problemas

### La cámara no funciona
- Verifica que tienes PSRAM habilitado
- Revisa las conexiones de la cámara
- Chequea el Monitor Serie para mensajes de error

### Los motores no se mueven
- Verifica las conexiones del L298N
- Asegúrate de tener alimentación externa
- Revisa que los jumpers ENA/ENB estén quitados en el L298N

### No puedo conectarme al WiFi
- Espera 10-20 segundos después de encender para que se cree el AP
- Verifica el SSID y contraseña en el código
- Reinicia el ESP32 si es necesario

### El servo no responde
- Verifica la conexión en el pin correcto
- Asegúrate de tener la librería ESP32Servo instalada
- Algunos servos requieren alimentación externa

## 📝 Personalización

### Cambiar Credenciales WiFi
```cpp
const char* ap_ssid = "MiRobot";
const char* ap_password = "MiPassword123";
```

### Ajustar Velocidad Predeterminada
```cpp
int motorSpeed = 150;  // Reducir para motores más lentos
```

### Cambiar Posición Inicial del Servo
```cpp
myServo.write(45);  // En el setup()
```

### Modificar Resolución de Cámara
En la función `setupCamera()`:
```cpp
config.frame_size = FRAMESIZE_QVGA;  // Menor resolución, más rápido
```

## 📄 Licencia

Este código es de uso educativo y libre. Puedes modificarlo y distribuirlo libremente.

## 👨‍💻 Autor

Sistema Integrado PuertoVaras - Noviembre 2025

---

¡Disfruta experimentando con tu ESP32! 🎉
