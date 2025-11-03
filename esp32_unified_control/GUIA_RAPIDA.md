# 🚀 GUÍA RÁPIDA DE INICIO
## ESP32 Unified Control System

### ⚡ Inicio Rápido (5 pasos)

#### 1. PREPARAR ARDUINO IDE
```
✓ Instalar librería ESP32Servo
✓ Configurar board: AI Thinker ESP32-CAM
✓ Partition Scheme: Huge APP (3MB)
✓ PSRAM: Enabled
```

#### 2. CONECTAR HARDWARE
```
✓ ESP32-CAM + Programador FTDI/USB
✓ L298N con batería 7-12V
✓ Motores a OUT1-OUT4 del L298N
✓ Servo a GPIO 13
✓ GND común en todos los componentes
```

#### 3. SUBIR CÓDIGO
```
1. Abrir esp32_unified_control.ino
2. Verificar y compilar
3. Conectar GPIO 0 a GND para modo programación
4. Subir código
5. Desconectar GPIO 0 de GND
6. Presionar RESET
```

#### 4. CONECTAR AL WiFi
```
1. Buscar red: "ESP32-Control"
2. Contraseña: "12345678"
3. Conectarse desde celular/PC
```

#### 5. ABRIR INTERFAZ WEB
```
Navegador: http://192.168.4.1
```

---

### 📱 Acceso desde Diferentes Dispositivos

#### Desde Celular (Android/iPhone)
1. Configuración → WiFi
2. Conectar a "ESP32-Control"
3. Abrir Chrome/Safari
4. Ir a: 192.168.4.1

#### Desde PC/Laptop (Windows/Mac/Linux)
1. Configuración de Red → WiFi
2. Conectar a "ESP32-Control"
3. Abrir navegador
4. Ir a: 192.168.4.1

#### Desde Tablet
Mismo proceso que celular

---

### 🎮 Controles Disponibles

| Función | Acción |
|---------|--------|
| 💡 LED ON/OFF | Encender/apagar LED flash |
| 🚗 Motores | Avanzar, retroceder, girar |
| ⚡ Velocidad | Slider 0-255 |
| 🎚️ Servo | Slider 0-180° |
| 📹 Cámara | Stream automático |

---

### ⚙️ Configuración Rápida

#### Cambiar Nombre WiFi
```cpp
// Línea 24-25 en el .ino
const char* ap_ssid = "MiRobot";
const char* ap_password = "MiClave123";
```

#### Ajustar Velocidad Inicial
```cpp
// Línea 51
int motorSpeed = 150;  // 0-255
```

#### Cambiar Pin del LED (si hay conflicto)
```cpp
// Línea 22
#define LED_PIN 2  // Cambiar a otro pin
```

#### Reducir Resolución de Cámara (más FPS)
```cpp
// Línea 309 en setupCamera()
config.frame_size = FRAMESIZE_QVGA;  // 320x240
```

---

### 🔍 Monitor Serie (Debug)

Baudrate: **115200**

Mensajes esperados:
```
Iniciando ESP32 Unified Control System...
Configurando Access Point...
IP del Access Point: 192.168.4.1
Cámara inicializada correctamente
Servidor Web iniciado!
====================================
Conéctate a la red WiFi:
  SSID: ESP32-Control
  Password: 12345678
Luego abre en tu navegador:
  http://192.168.4.1
====================================
```

---

### ❗ Solución Rápida de Problemas

#### ❌ No compila
→ Instalar librería ESP32Servo
→ Verificar Partition Scheme (Huge APP)

#### ❌ No aparece WiFi
→ Esperar 20 segundos
→ Revisar password (mínimo 8 caracteres)
→ Resetear ESP32

#### ❌ Motores no funcionan
→ Verificar batería externa conectada
→ Quitar jumpers ENA/ENB del L298N
→ Revisar conexiones IN1-IN4

#### ❌ Cámara no funciona
→ PSRAM debe estar habilitado
→ Partition Scheme correcto
→ Reducir resolución a QVGA

#### ❌ Servo no responde
→ Verificar pin GPIO 13
→ Librería ESP32Servo instalada
→ Alimentación 5V conectada

---

### 📊 Especificaciones Técnicas

| Parámetro | Valor |
|-----------|-------|
| Placa | ESP32-CAM AI-THINKER |
| WiFi | 802.11 b/g/n |
| Frecuencia | 2.4 GHz |
| Alcance AP | 10-30 metros |
| PWM Motores | 5 kHz, 8-bit (0-255) |
| PWM Servo | 50 Hz, 0-180° |
| Cámara | OV2640, hasta 1600x1200 |
| FPS (VGA) | 10-15 fps típico |
| Memoria Flash | ~60% usado |
| RAM | ~200KB para streaming |

---

### 🔋 Requerimientos de Energía

| Componente | Consumo |
|------------|---------|
| ESP32-CAM | 200-300 mA |
| Cámara activa | +100 mA |
| Servo SG90 | 100-500 mA |
| Motor DC (cada uno) | 500-1500 mA |
| **Total estimado** | **2-4 A** |

**Recomendación:** Batería 7.4V 2S Li-Po de al menos 2000mAh

---

### 🎯 Checklist Pre-vuelo

Antes de encender, verificar:

- [ ] Código subido correctamente
- [ ] Monitor serie muestra IP
- [ ] Batería cargada y conectada
- [ ] GND común en todos los componentes
- [ ] No hay cables sueltos
- [ ] Jumpers ENA/ENB quitados del L298N
- [ ] Motores pueden girar libremente
- [ ] Servo tiene alimentación
- [ ] Polaridad correcta en batería

---

### 📞 Recursos Adicionales

**Archivos incluidos:**
- `esp32_unified_control.ino` - Código principal
- `camera_pins.h` - Configuración de pines de cámara
- `README.md` - Documentación completa
- `NOTAS_CONFIGURACION.txt` - Notas técnicas
- `DIAGRAMA_CONEXIONES.txt` - Diagramas de conexión
- `preview.html` - Vista previa de interfaz
- `GUIA_RAPIDA.md` - Este archivo

**URLs útiles:**
- ESP32Servo Library: https://github.com/madhephaestus/ESP32Servo
- ESP32 Camera: https://github.com/espressif/esp32-camera
- Arduino ESP32: https://github.com/espressif/arduino-esp32

---

### 💡 Tips y Trucos

1. **Mejor FPS en cámara:** Usa QVGA (320x240) en lugar de VGA
2. **Mayor alcance WiFi:** Coloca ESP32 en alto, lejos de metal
3. **Motores más suaves:** Reduce velocidad inicial a 150
4. **Ahorro de energía:** Apaga LED cuando no lo uses
5. **Múltiples pruebas:** Desconecta batería entre pruebas
6. **Depuración fácil:** Siempre revisa Monitor Serie primero
7. **Evita reinicios:** No conectes/desconectes con alimentación
8. **Streaming fluido:** Cierra otras apps en el celular
9. **Control preciso:** Usa sliders en lugar de botones
10. **Seguridad:** Agrega un interruptor físico a la batería

---

### 🎉 ¡Listo para Usar!

Tu ESP32 Control System está configurado y listo.

**Primera prueba:**
1. Enciende el sistema
2. Conéctate al WiFi
3. Abre 192.168.4.1
4. Prueba el LED primero
5. Luego prueba servo
6. Finalmente prueba motores (con cuidado)
7. Observa el streaming de cámara

**¡Disfruta!** 🚀

---

*Documento creado: Noviembre 2025*
*Versión: 1.0*
