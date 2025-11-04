#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include "esp_camera.h"

// ===========================
// Incluir los HTMLs
// ===========================
#include "menu_principal.h"
#include "robot_control.h"

// ===========================
// Configuración WiFi (Access Point)
// ===========================
const char* ap_ssid = "ESP32-Ejemplo";
const char* ap_password = "12345678";

// ===========================
// Configuración de Pines
// ===========================
#define LED_PIN 4
const int motor1Pin1 = 14;  // IN1
const int motor1Pin2 = 15;  // IN2
const int motor2Pin1 = 13;  // IN3
const int motor2Pin2 = 12;  // IN4
#define SERVO_PIN 2

// ===========================
// Servidores Web
// ===========================
WebServer server(80);           // Servidor para controles (Core 1)
WebServer streamServer(81);     // Servidor para video (Core 0) 

// Variables globales
Servo myServo;
bool ledState = false;
int servoPosition = 90;
bool cameraInitialized = false;

// Variable para elegir el estilo del menú (1=Terminal, 2=Modern, 3=Campus)
#define MENU_STYLE 3  // <-- CAMBIA ESTE NÚMERO PARA ELEGIR EL ESTILO (1, 2 o 3)

// ===========================
// Configuración de la Cámara
// ===========================
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===========================
// HTML de la Interfaz de Prueba de Componentes
// ===========================
const char PROBAR_COMPONENTES_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Control Panel</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            padding: 20px;
            min-height: 100vh;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        .back-button {
            background: rgba(255, 255, 255, 0.2);
            border: 2px solid white;
            color: white;
            padding: 10px 20px;
            text-decoration: none;
            display: inline-block;
            margin-bottom: 20px;
            border-radius: 8px;
            font-weight: bold;
            transition: all 0.3s;
        }
        .back-button:hover {
            background: rgba(255, 255, 255, 0.3);
            transform: scale(1.05);
        }
        h1 {
            text-align: center;
            color: white;
            margin-bottom: 30px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        .control-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 20px;
            margin-bottom: 20px;
        }
        .card {
            background: white;
            border-radius: 15px;
            padding: 25px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            transition: transform 0.3s;
        }
        .card:hover {
            transform: translateY(-5px);
        }
        .card h2 {
            color: #667eea;
            margin-bottom: 20px;
            font-size: 1.5em;
            border-bottom: 2px solid #667eea;
            padding-bottom: 10px;
        }
        .btn {
            width: 100%;
            padding: 15px;
            margin: 8px 0;
            border: none;
            border-radius: 8px;
            font-size: 16px;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s;
            color: white;
        }
        .btn:hover {
            transform: scale(1.05);
            box-shadow: 0 5px 15px rgba(0,0,0,0.3);
        }
        .btn-primary { background: #667eea; }
        .btn-success { background: #48bb78; }
        .btn-danger { background: #f56565; }
        .btn-warning { background: #ed8936; }
        .btn-info { background: #4299e1; }
        .btn-secondary { background: #718096; }
        
        .slider-container {
            margin: 15px 0;
        }
        .slider-container label {
            display: block;
            margin-bottom: 8px;
            color: #4a5568;
            font-weight: bold;
        }
        input[type="range"] {
            width: 100%;
            height: 8px;
            border-radius: 5px;
            background: #e2e8f0;
            outline: none;
            -webkit-appearance: none;
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: #667eea;
            cursor: pointer;
        }
        .value-display {
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            color: #667eea;
            margin: 10px 0;
        }
        .camera-container {
            grid-column: 1 / -1;
        }
        .camera-view {
            width: 100%;
            border-radius: 10px;
            margin-top: 15px;
            background-color: #333; 
        }
        .status-indicator {
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            margin-right: 8px;
        }
        .status-on { background: #48bb78; }
        .status-off { background: #cbd5e0; }
        @media (max-width: 768px) {
            .control-grid {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <a href="/" class="back-button">← Volver al Menú</a>
        <h1>🎛️ ESP32 Control Panel</h1>
        
        <div class="control-grid">
            
            <div class="card">
                <h2>💡 LED Control</h2>
                <button class="btn btn-success" onclick="controlLED('on')">Encender LED</button>
                <button class="btn btn-danger" onclick="controlLED('off')">Apagar LED</button>
                <div style="margin-top: 15px; text-align: center;">
                    <span class="status-indicator" id="ledStatus"></span>
                    <span id="ledText">Desconocido</span>
                </div>
            </div>

            <div class="card">
                <h2>🚗 Control de Motores</h2>
                <button class="btn btn-primary" onclick="controlMotor('forward')">⬆️ Avanzar</button>
                <button class="btn btn-info" onclick="controlMotor('left')">⬅️ Girar Izq.</button>
                <button class="btn btn-info" onclick="controlMotor('right')">➡️ Girar Der.</button>
                <button class="btn btn-warning" onclick="controlMotor('backward')">⬇️ Retroceder</button>
                <button class="btn btn-danger" onclick="controlMotor('stop')">⏹️ Detener</button>
            </div>

            <div class="card">
                <h2>🎚️ Control de Servo</h2>
                <div class="slider-container">
                    <label>Posición (grados)</label>
                    <div class="value-display" id="servoValue">90°</div>
                    <input type="range" min="0" max="180" value="90" id="servoSlider" 
                            oninput="updateServoDisplay(this.value)"
                            onchange="setServoPosition(this.value)">
                </div>
                <button class="btn btn-primary" onclick="setServoPosition(0)">0°</button>
                <button class="btn btn-primary" onclick="setServoPosition(90)">90°</button>
                <button class="btn btn-primary" onclick="setServoPosition(180)">180°</button>
            </div>
            <div class="card camera-container">
                <h2>📹 Cámara en Vivo</h2>
                <img src="%%STREAM_URL%%" class="camera-view" onerror="this.style.display='none'; document.getElementById('camError').style.display='block';">
                <div id="camError" style="display:none; text-align:center; padding: 20px; color: #f56565; font-weight: bold;">
                    Error al cargar el stream de la cámara.
                </div>
            </div>
        </div>
    </div>

    <script>
        // Update displays
        function updateServoDisplay(value) {
            document.getElementById('servoValue').textContent = value + '°';
        }

        // LED Control
        function controlLED(action) {
            fetch('/led?action=' + action)
                .then(response => response.text())
                .then(data => {
                    const status = document.getElementById('ledStatus');
                    const text = document.getElementById('ledText');
                    if(action === 'on') {
                        status.className = 'status-indicator status-on';
                        text.textContent = 'Encendido';
                    } else {
                        status.className = 'status-indicator status-off';
                        text.textContent = 'Apagado';
                    }
                });
        }

        // Motor Control
        function controlMotor(action) {
            fetch('/motor?action=' + action)
                .then(response => response.text())
                .then(data => console.log(data));
        }

        // Servo Control
        function setServoPosition(position) {
            document.getElementById('servoSlider').value = position;
            updateServoDisplay(position);
            fetch('/servo?position=' + position)
                .then(response => response.text())
                .then(data => console.log(data));
        }

        // Initialize
        window.onload = function() {
            const status = document.getElementById('ledStatus');
            const text = document.getElementById('ledText');
            status.className = 'status-indicator status-off';
            text.textContent = 'Apagado';
            updateServoDisplay(document.getElementById('servoSlider').value);
        }
    </script>
</body>
</html>
)rawliteral";

// ===========================
// Funciones de Control
// ===========================

void setupCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    
    if (psramFound()) {
        config.frame_size = FRAMESIZE_CIF;  // Optimizado: 400x296 (era VGA 640x480)
        config.jpeg_quality = 15;           // Optimizado: Mayor compresión (era 10)
        config.fb_count = 1;                // Optimizado: Menos buffers (era 2) - PROBAR
        config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
        config.frame_size = FRAMESIZE_QVGA; 
        config.jpeg_quality = 15;           // Optimizado: Mayor compresión (era 12)
        config.fb_count = 1; 
        config.fb_location = CAMERA_FB_IN_DRAM;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Error al iniciar cámara: 0x%x\n", err);
        cameraInitialized = false;
        return;
    }
    
    cameraInitialized = true;
    Serial.println("Cámara inicializada correctamente");
}

// Control de LED
void handleLED() {
    if (server.hasArg("action")) {
        String action = server.arg("action");
        if (action == "on") {
            digitalWrite(LED_PIN, HIGH); 
            ledState = true;
            server.send(200, "text/plain", "LED Encendido");
        } else if (action == "off") {
            digitalWrite(LED_PIN, LOW); 
            ledState = false;
            server.send(200, "text/plain", "LED Apagado");
        }
    }
}

void motorForward() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void motorBackward() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void motorLeft() { 
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void motorRight() { 
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void motorStop() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}

void handleMotor() {
    if (server.hasArg("action")) {
        String action = server.arg("action");
        if (action == "forward") motorForward();
        if (action == "backward") motorBackward();
        if (action == "left") motorLeft();
        if (action == "right") motorRight();
        if (action == "stop") motorStop();
        server.send(200, "text/plain", "Motor: " + action);
    }
}

void handleServo() {
    if (server.hasArg("position")) {
        servoPosition = server.arg("position").toInt();
        myServo.write(servoPosition);
        server.send(200, "text/plain", "Servo en posición: " + String(servoPosition));
    }
}

// Handler del menú principal (raíz)
void handleRoot() {
    String menuHTML;
    
    // Seleccionar el estilo de menú según la configuración
    #if MENU_STYLE == 1
        menuHTML = FPSTR(MENU_STYLE_TERMINAL);
    #elif MENU_STYLE == 2
        menuHTML = FPSTR(MENU_STYLE_MODERN);
    #else
        menuHTML = FPSTR(MENU_STYLE_CAMPUS);
    #endif
    
    server.send(200, "text/html", menuHTML);
}

// Handler de la página de prueba de componentes
void handleProbar() {
    String html = FPSTR(PROBAR_COMPONENTES_HTML);
    String streamURL = "http://" + WiFi.softAPIP().toString() + ":81/stream";
    html.replace("%%STREAM_URL%%", streamURL);
    server.send(200, "text/html", html);
}

// Handler de la página de control del robot
void handleRobot() {
    String html = FPSTR(ROBOT_CONTROL_HTML);
    server.send(200, "text/html", html);
}

// Handler del streaming de video
void handleStream() {
    if (!cameraInitialized) {
        streamServer.send(503, "text/plain", "Cámara no disponible");
        return;
    }

    WiFiClient client = streamServer.client(); 
    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: multipart/x-mixed-replace; boundary=frame");
    client.println();
    
    while (client.connected()) {
        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Error capturando imagen");
            break;
        }
        
        client.println("--frame");
        client.println("Content-Type: image/jpeg");
        client.print("Content-Length: ");
        client.println(fb->len);
        client.println();
        client.write(fb->buf, fb->len);
        client.println();
        
        esp_camera_fb_return(fb);
        
        if (!client.connected()) break;
        
        // Optimizado: Delay para liberar CPU (~25 FPS)
        delay(40);
    }
}

// ===================================
// TAREA PARA EL NÚCLEO 0 (Streaming)
// ===================================
void streamTask(void *pvParameters) {
    streamServer.on("/stream", handleStream);
    streamServer.begin();
    Serial.println("Servidor de Streaming iniciado en Núcleo 0 (Puerto 81)");

    for (;;) {
        streamServer.handleClient();
        vTaskDelay(1); 
    }
}

// ===========================
// Setup (Corre en Núcleo 1)
// ===========================
void setup() {
    Serial.begin(115200);
    Serial.println("\n\n╔════════════════════════════════════════════╗");
    Serial.println("║   MAKER CAMPUS - ESP32 ROBOT SYSTEM v2.0  ║");
    Serial.println("╚════════════════════════════════════════════╝\n");

    // Configurar LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Configurar Motores
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    motorStop();

    // Configurar Servo
    myServo.attach(SERVO_PIN);
    myServo.write(90);

    // Configurar Cámara
    setupCamera();

    // Configurar WiFi en modo AP
    Serial.println("→ Configurando Access Point...");
    WiFi.softAP(ap_ssid, ap_password);
    
    IPAddress IP = WiFi.softAPIP();
    Serial.print("→ IP del Access Point: ");
    Serial.println(IP);

    // Configurar rutas del servidor web (Núcleo 1)
    server.on("/", handleRoot);              // Menú principal
    server.on("/probar", handleProbar);      // Interfaz de prueba
    server.on("/robot", handleRobot);        // Interfaz de control del robot
    server.on("/led", handleLED);            // Endpoint LED
    server.on("/motor", handleMotor);        // Endpoint Motor
    server.on("/servo", handleServo);        // Endpoint Servo

    // Iniciar servidor de controles
    server.begin();
    Serial.println("→ Servidor Web iniciado en Núcleo 1 (Puerto 80)");

    // Iniciar la tarea de streaming en el Núcleo 0
    xTaskCreatePinnedToCore(
        streamTask,         // Función de la tarea
        "StreamTask",       // Nombre de la tarea
        4096,               // Tamaño de la pila (stack)
        NULL,               // Parámetros de la tarea
        1,                  // Prioridad
        NULL,               // Handle de la tarea (opcional)
        0                   // Núcleo 0
    );

    Serial.println("\n╔════════════════════════════════════════════╗");
    Serial.println("║          SISTEMA LISTO Y OPERATIVO         ║");
    Serial.println("╠════════════════════════════════════════════╣");
    Serial.print("║  SSID: ");
    Serial.print(ap_ssid);
    Serial.println("                            ║");
    Serial.print("║  URL:  http://");
    Serial.print(IP);
    Serial.println("               ║");
    Serial.println("║                                            ║");
    Serial.println("║  Rutas disponibles:                        ║");
    Serial.println("║    /       → Menú Principal                ║");
    Serial.println("║    /probar → Probar Componentes            ║");
    Serial.println("║    /robot  → Controlar Robot               ║");
    Serial.println("╚════════════════════════════════════════════╝\n");
}

// ===========================
// Loop (Corre en Núcleo 1)
// ===========================
void loop() {
    // El loop principal solo maneja el servidor de controles
    server.handleClient();
}
