#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include "esp_camera.h"

// ===========================
// Configuración WiFi (Access Point)
// ===========================
const char* ap_ssid = "ESP32-Control";
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

// ===========================
// Configuración de la Cámara
// ===========================
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===========================
// HTML de la Interfaz Web
// ===========================
const char HTML_PAGE_TEMPLATE[] PROGMEM = R"rawliteral(
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
            // Setea el estado inicial del LED como apagado
            const status = document.getElementById('ledStatus');
            const text = document.getElementById('ledText');
            status.className = 'status-indicator status-off';
            text.textContent = 'Apagado';
            
            // Setea el estado inicial del servo
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
    
    // <-- CAMBIO EN LA LÓGICA DE PSRAM
    if (psramFound()) {
        config.frame_size = FRAMESIZE_VGA; 
        config.jpeg_quality = 10;
        config.fb_count = 2; 
        config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
        config.frame_size = FRAMESIZE_QVGA; 
        config.jpeg_quality = 12;
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
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}
void motorBackward() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}
void motorLeft() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}
void motorRight() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
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

void handleRoot() {
    String html = HTML_PAGE_TEMPLATE;
    
    String streamURL = "http://" + WiFi.softAPIP().toString() + ":81/stream";
    html.replace("%%STREAM_URL%%", streamURL);
    
    server.send(200, "text/html", html);
}

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
    }
}

// ===================================
// <-- NÚCLEO 0 -->
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
    Serial.println("\n\nIniciando ESP32 Unified Control System (Doble Núcleo)...");

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
    Serial.println("Configurando Access Point...");
    WiFi.softAP(ap_ssid, ap_password);
    
    IPAddress IP = WiFi.softAPIP();
    Serial.print("IP del Access Point: ");
    Serial.println(IP);

    // Configurar rutas del servidor web (Núcleo 1)
    server.on("/", handleRoot);
    server.on("/led", handleLED);
    server.on("/motor", handleMotor);
    server.on("/servo", handleServo);

    // Iniciar servidor de controles
    server.begin();
    Serial.println("Servidor Web (Controles) iniciado en Núcleo 1 (Puerto 80)");

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

    Serial.println("====================================");
    Serial.println("Sistema listo. Conéctate a la red:");
    Serial.print("   SSID: "); Serial.println(ap_ssid);
    Serial.println("Abre en tu navegador:");
    Serial.print("   http://"); Serial.println(IP);
    Serial.println("====================================");
}

// ===========================
// Loop (Corre en Núcleo 1)
// ===========================
void loop() {
    // El loop principal solo maneja el servidor de controles
    server.handleClient();
}