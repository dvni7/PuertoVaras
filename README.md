# 🤖 ESP32-CAM Robot Control System v2.0
## Maker Campus - Puerto Varas Project

Sistema unificado de control para robot ESP32-CAM con menú de navegación y dos interfaces:
- **Probar Componentes**: Testing individual de LED, motores, servo y cámara
- **Controlar Robot**: Interfaz táctil optimizada para tablet con streaming en vivo

---

## 📁 Estructura del Proyecto

```
PuertoVaras/
├── PuertoVaras.ino          # Código principal unificado
├── camera_pins.h            # Configuración de pines de la cámara
├── menu_principal.h         # 3 estilos de menú (Terminal, Modern, Campus)
└── robot_control.h          # Interfaz mejorada de control táctil
```

---

## 🎨 Estilos de Menú Disponibles

El sistema incluye **3 estilos diferentes** del menú principal. Para cambiar entre ellos:

1. Abre `PuertoVaras.ino`
2. Busca la línea (aprox. línea 28):
   ```cpp
   #define MENU_STYLE 3  // <-- CAMBIA ESTE NÚMERO
   ```
3. Cambia el número por:
   - `1` = **Terminal**: Estilo monocromático tipo consola retro
   - `2` = **Modern**: Cards modernas con gradientes y blur effects
   - `3` = **Campus**: Diseño con branding de Maker Campus (por defecto)

---

## 🔧 Configuración de Hardware

### Pines Utilizados:
- **LED**: GPIO 4
- **Motor 1**: GPIO 14 (IN1), GPIO 15 (IN2)
- **Motor 2**: GPIO 13 (IN3), GPIO 12 (IN4)
- **Servo**: GPIO 2
- **Cámara**: Configuración AI-THINKER (ver camera_pins.h)

### WiFi Access Point:
- **SSID**: `ESP32-04`
- **Password**: `12345678`
- **IP**: `192.168.4.1`

---

## 🚀 Cómo Usar

### 1. Cargar el Código
1. Abre `PuertoVaras.ino` en Arduino IDE
2. Selecciona la placa: **AI Thinker ESP32-CAM**
3. Configuración recomendada:
   - **Partition Scheme**: Huge APP (3MB No OTA/1MB SPIFFS)
   - **PSRAM**: Enabled
4. Conecta el ESP32-CAM con un programador FTDI
5. Sube el código

### 2. Conectarse al Robot
1. Conecta tu tablet/smartphone/PC al WiFi:
   - Red: `ESP32-04`
   - Contraseña: `12345678`
2. Abre el navegador y ve a: `http://192.168.4.1`
3. Verás el menú principal con 2 opciones

### 3. Navegar por las Interfaces

#### 📋 Menú Principal (`http://192.168.4.1/`)
- Selecciona entre "Probar Componentes" o "Controlar Robot"
- Cada opción te llevará a su interfaz correspondiente

#### 🔧 Probar Componentes (`/probar`)
- Control individual de cada componente
- Ideal para diagnóstico y verificación
- Streaming de cámara integrado
- Botón "Volver al Menú" en la esquina superior izquierda

#### 🎮 Controlar Robot (`/robot`)
- **Navegación**: Botones táctiles grandes para tablet
  - ↑ Adelante
  - ↓ Atrás
  - ← Izquierda
  - → Derecha
  - ⏹ Stop (botón rojo central)
- **LED**: Botones ON/OFF
- **Servo**: Slider + botones preestablecidos (0°, 90°, 180°)
- **Cámara**: Streaming en vivo con botón Start/Stop
- Botón "Volver al Menú" en el header

---

## 🌐 Endpoints Disponibles

### Páginas:
- `/` - Menú principal
- `/probar` - Interfaz de prueba de componentes
- `/robot` - Interfaz de control del robot

### API:
- `/led?action=on` - Encender LED
- `/led?action=off` - Apagar LED
- `/motor?action=forward` - Mover adelante
- `/motor?action=backward` - Mover atrás
- `/motor?action=left` - Girar izquierda
- `/motor?action=right` - Girar derecha
- `/motor?action=stop` - Detener motores
- `/servo?position=90` - Mover servo (0-180)

### Streaming:
- `http://192.168.4.1:81/stream` - Video streaming (puerto 81)

---

## ⚡ Arquitectura Dual-Core

El sistema aprovecha los dos núcleos del ESP32:

- **Core 1** (Main):
  - Servidor web principal (puerto 80)
  - Procesamiento de comandos
  - Control de periféricos
  
- **Core 0** (Streaming):
  - Servidor de video dedicado (puerto 81)
  - Captura y envío de frames
  - No interfiere con los controles

Esto garantiza que el streaming de video no afecte la respuesta de los controles.

---

## 📱 Optimizaciones para Tablet

- **Touch-friendly**: Botones grandes (25px padding mínimo)
- **Sin zoom accidental**: `user-scalable=no`
- **Tap highlight deshabilitado**: Evita parpadeos en toques
- **Prevención de double-tap**: Evita zoom por doble toque
- **Responsive**: Se adapta a diferentes tamaños de pantalla

---

## 🎨 Paleta de Colores

El sistema usa una paleta consistente:
- **Primario**: `#FF6B35` (Naranja vibrante)
- **Secundario**: `#F7931E` (Ámbar dorado)
- **Fondo**: `#0F0701` (Negro profundo)
- **Texto**: `rgb(255, 174, 0)` (Naranja brillante)

---

## 🔍 Solución de Problemas

### La cámara no funciona
- Verifica que PSRAM esté habilitado
- Revisa las conexiones de los pines de la cámara
- Mira el Serial Monitor para mensajes de error

### Los controles no responden
- Verifica que estés conectado al WiFi correcto
- Revisa que la IP sea `192.168.4.1`
- Comprueba el Serial Monitor para ver si llegan las peticiones

### El streaming va muy lento
- Reduce la calidad en `setupCamera()` (aumenta `jpeg_quality`)
- Cambia `FRAMESIZE_VGA` a `FRAMESIZE_QVGA`
- Asegúrate de que haya PSRAM disponible

### No aparece el menú
- Verifica que `MENU_STYLE` esté entre 1 y 3
- Comprueba que los archivos `.h` estén en el mismo directorio

---

## 📝 Personalización

### Cambiar el WiFi AP
Edita en `PuertoVaras.ino`:
```cpp
const char* ap_ssid = "TU_NOMBRE";
const char* ap_password = "TU_CONTRASEÑA";
```

### Cambiar pines
Edita las definiciones al inicio de `PuertoVaras.ino`:
```cpp
#define LED_PIN 4
const int motor1Pin1 = 14;
// etc...
```

### Personalizar el menú
Edita `menu_principal.h` y modifica el CSS de cada estilo.

### Personalizar la interfaz de control
Edita `robot_control.h` para cambiar colores, layout, o agregar funciones.

---

## 📊 Características Técnicas

- **Plataforma**: ESP32-CAM (AI-THINKER)
- **Framework**: Arduino
- **Servidor Web**: WebServer (puerto 80 y 81)
- **Streaming**: Motion JPEG over HTTP
- **Resolución**: VGA (640x480) con PSRAM, QVGA sin PSRAM
- **Arquitectura**: Dual-core (FreeRTOS)
- **Memoria**: 4MB Flash, PSRAM opcional

---

## 🏆 Créditos

**Maker Campus** - Puerto Varas Project
© 2025

Desarrollado para control de robot educativo con ESP32-CAM.

---

## 📄 Licencia

Código libre para uso educativo y personal.

---

¿Necesitas ayuda? Revisa el código o contacta al equipo de Maker Campus.
