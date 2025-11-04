/*
 * Interfaz de Control del Robot - Optimizada para Touch/Tablet
 * Con backend conectado a los endpoints reales de ESP32-CAM
 */

const char ROBOT_CONTROL_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Control Robot - Maker Campus</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Share+Tech+Mono&display=swap');
        * { margin: 0; padding: 0; box-sizing: border-box; -webkit-tap-highlight-color: transparent; }
        body {
            font-family: 'Share Tech Mono', monospace;
            background: rgb(15, 7, 1);
            color: rgb(255, 174, 0);
            min-height: 100vh;
            padding: 15px;
            touch-action: manipulation;
        }
        .wrapper { max-width: 1400px; margin: 0 auto; }
        
        /* Header */
        .header {
            background: rgba(0,0,0,0.75);
            border: 2px solid rgb(255, 174, 0);
            padding: 15px 20px;
            margin-bottom: 15px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            flex-wrap: wrap;
            gap: 15px;
        }
        .header h1 {
            font-size: 1.5rem;
            letter-spacing: 0.1em;
        }
        .header .status {
            font-size: 0.85rem;
            color: #F7931E;
        }
        .back-button {
            background: rgba(255, 107, 53, 0.2);
            border: 2px solid #FF6B35;
            color: #FF6B35;
            padding: 10px 20px;
            text-decoration: none;
            font-family: inherit;
            font-size: 0.9rem;
            letter-spacing: 0.05em;
            cursor: pointer;
            transition: all 0.2s;
        }
        .back-button:hover {
            background: rgba(255, 107, 53, 0.4);
            box-shadow: 0 0 15px rgba(255, 107, 53, 0.5);
        }
        
        /* Main Grid */
        .main-grid {
            display: grid;
            grid-template-columns: 1fr 2fr;
            gap: 15px;
        }
        
        /* Panels */
        .panel {
            background: rgba(0,0,0,0.75);
            border: 2px solid rgb(255, 174, 0);
            padding: 20px;
        }
        .panel h2 {
            font-size: 1.1rem;
            margin-bottom: 20px;
            padding-bottom: 10px;
            border-bottom: 1px solid rgba(255, 174, 0, 0.4);
            letter-spacing: 0.1em;
        }
        
        /* Control Buttons */
        .section-title {
            font-size: 0.85rem;
            color: #F7931E;
            margin-bottom: 15px;
            letter-spacing: 0.08em;
            text-transform: uppercase;
        }
        .control-grid {
            display: grid;
            gap: 12px;
        }
        .direction-grid {
            grid-template-columns: repeat(3, 1fr);
            grid-template-rows: repeat(3, 1fr);
        }
        .rotation-grid {
            grid-template-columns: repeat(2, 1fr);
        }
        
        .btn {
            background: rgba(90,52,0,0.2);
            border: 3px solid rgb(255, 174, 0);
            color: rgb(255, 174, 0);
            padding: 25px 15px;
            font-family: inherit;
            font-size: 1.1rem;
            font-weight: 600;
            letter-spacing: 0.05em;
            cursor: pointer;
            transition: all 0.15s;
            text-transform: uppercase;
            touch-action: manipulation;
            user-select: none;
        }
        .btn:active {
            background: rgba(255, 174, 0, 0.3);
            box-shadow: 0 0 20px rgba(255, 174, 0, 0.6);
            transform: scale(0.95);
        }
        
        /* Direction buttons positioning */
        .btn-up { grid-column: 2; grid-row: 1; }
        .btn-left { grid-column: 1; grid-row: 2; }
        .btn-stop { grid-column: 2; grid-row: 2; background: rgba(127,29,29,0.25); border-color: #f87171; color: #fca5a5; }
        .btn-right { grid-column: 3; grid-row: 2; }
        .btn-down { grid-column: 2; grid-row: 3; }
        
        .btn-stop:active { 
            background: rgba(239,68,68,0.35);
            box-shadow: 0 0 20px rgba(239,68,68,0.6);
        }
        
        /* LED Controls */
        .led-controls {
            display: flex;
            gap: 12px;
        }
        .led-controls .btn {
            flex: 1;
        }
        .btn-led-on { border-color: #48bb78; color: #48bb78; }
        .btn-led-off { border-color: #f56565; color: #f56565; }
        
        /* Servo Controls */
        .servo-slider {
            margin: 20px 0;
        }
        .servo-value {
            text-align: center;
            font-size: 2rem;
            font-weight: bold;
            color: rgb(255, 174, 0);
            margin: 15px 0;
        }
        .servo-value .unit {
            font-size: 1rem;
        }
        input[type="range"] {
            width: 100%;
            height: 12px;
            border-radius: 6px;
            background: rgba(255, 174, 0, 0.2);
            outline: none;
            -webkit-appearance: none;
            margin: 15px 0;
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 30px;
            height: 30px;
            border-radius: 50%;
            background: rgb(255, 174, 0);
            cursor: pointer;
            box-shadow: 0 0 10px rgba(255, 174, 0, 0.5);
        }
        input[type="range"]::-moz-range-thumb {
            width: 30px;
            height: 30px;
            border-radius: 50%;
            background: rgb(255, 174, 0);
            cursor: pointer;
            border: none;
            box-shadow: 0 0 10px rgba(255, 174, 0, 0.5);
        }
        .servo-presets {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 10px;
        }
        .servo-presets .btn {
            padding: 15px 10px;
            font-size: 1rem;
        }
        
        /* Camera Panel */
        .camera-panel {
            display: flex;
            flex-direction: column;
            gap: 15px;
        }
        .stream-wrapper {
            position: relative;
            border: 2px solid rgb(255, 174, 0);
            background: rgb(15, 7, 1);
            aspect-ratio: 16/9;
            overflow: hidden;
        }
        .stream-wrapper img {
            width: 100%;
            height: 100%;
            object-fit: contain;
        }
        .stream-overlay {
            position: absolute;
            top: 10px;
            left: 10px;
            background: rgba(0, 0, 0, 0.8);
            border: 1px solid rgba(255, 174, 0, 0.5);
            padding: 8px 12px;
            font-size: 0.75rem;
            letter-spacing: 0.05em;
        }
        .stream-controls {
            display: flex;
            gap: 12px;
            flex-wrap: wrap;
        }
        .stream-controls .btn {
            flex: 1;
            min-width: 140px;
        }
        
        /* Status indicators */
        .status-dot {
            display: inline-block;
            width: 10px;
            height: 10px;
            border-radius: 50%;
            background: #f56565;
            margin-right: 8px;
            box-shadow: 0 0 8px rgba(245, 101, 101, 0.6);
        }
        .status-dot.active {
            background: rgb(255, 174, 0);
            box-shadow: 0 0 8px rgba(255, 174, 0, 0.8);
        }
        
        /* Responsive */
        @media (max-width: 1024px) {
            .main-grid {
                grid-template-columns: 1fr;
            }
        }
        @media (max-width: 640px) {
            .header h1 { font-size: 1.2rem; }
            .btn { padding: 20px 10px; font-size: 0.95rem; }
            .panel { padding: 15px; }
        }
    </style>
</head>
<body>
    <div class="wrapper">
        <div class="header">
            <h1>🤖 CONTROL DEL ROBOT</h1>
            <div class="status">
                <span class="status-dot" id="connection-status"></span>
                <span id="status-text">CONECTANDO...</span>
            </div>
            <a href="/" class="back-button">← VOLVER AL MENÚ</a>
        </div>
        
        <div class="main-grid">
            <!-- Left Panel: Controls -->
            <div class="panel">
                <h2>[ CONTROLES ]</h2>
                
                <!-- Motor Controls -->
                <div class="section-title">▸ NAVEGACIÓN</div>
                <div class="control-grid direction-grid">
                    <button class="btn btn-up" onclick="sendMotor('forward')">↑<br>ADELANTE</button>
                    <button class="btn btn-left" onclick="sendMotor('left')">←<br>IZQ</button>
                    <button class="btn btn-stop" onclick="sendMotor('stop')">⏹<br>STOP</button>
                    <button class="btn btn-right" onclick="sendMotor('right')">→<br>DER</button>
                    <button class="btn btn-down" onclick="sendMotor('backward')">↓<br>ATRÁS</button>
                </div>
                
                <!-- LED Controls -->
                <div class="section-title" style="margin-top: 25px;">▸ LED</div>
                <div class="led-controls">
                    <button class="btn btn-led-on" onclick="sendLED('on')">💡 ON</button>
                    <button class="btn btn-led-off" onclick="sendLED('off')">⚫ OFF</button>
                </div>
                
                <!-- Servo Controls -->
                <div class="section-title" style="margin-top: 25px;">▸ SERVO (CÁMARA)</div>
                <div class="servo-slider">
                    <div class="servo-value">
                        <span id="servo-display">90</span><span class="unit">°</span>
                    </div>
                    <input type="range" id="servo-slider" min="0" max="180" value="90" 
                           oninput="updateServoDisplay(this.value)"
                           onchange="sendServo(this.value)">
                </div>
                <div class="servo-presets">
                    <button class="btn" onclick="sendServo(0)">0°</button>
                    <button class="btn" onclick="sendServo(90)">90°</button>
                    <button class="btn" onclick="sendServo(180)">180°</button>
                </div>
            </div>
            
            <!-- Right Panel: Camera -->
            <div class="panel camera-panel">
                <h2>[ CÁMARA EN VIVO ]</h2>
                <div class="stream-wrapper">
                    <img id="camera-stream" src="" alt="Camera stream">
                    <div class="stream-overlay">
                        <span id="stream-status">STREAM: OFFLINE</span>
                    </div>
                </div>
                <div class="stream-controls">
                    <button class="btn" id="stream-toggle" onclick="toggleStream()">
                        ▶ INICIAR STREAM
                    </button>
                </div>
            </div>
        </div>
    </div>
    
    <script>
        // Configuration
        const baseURL = window.location.origin;
        const streamURL = baseURL + ':81/stream';
        let streamActive = false;
        
        // Get elements
        const streamImage = document.getElementById('camera-stream');
        const streamToggle = document.getElementById('stream-toggle');
        const streamStatus = document.getElementById('stream-status');
        const servoDisplay = document.getElementById('servo-display');
        const servoSlider = document.getElementById('servo-slider');
        const connectionStatus = document.getElementById('connection-status');
        const statusText = document.getElementById('status-text');
        
        // Update servo display
        function updateServoDisplay(value) {
            servoDisplay.textContent = value;
        }
        
        // Send motor command
        async function sendMotor(action) {
            try {
                const response = await fetch(baseURL + '/motor?action=' + action);
                if (response.ok) {
                    console.log('Motor:', action);
                }
            } catch (err) {
                console.error('Motor error:', err);
            }
        }
        
        // Send LED command
        async function sendLED(action) {
            try {
                const response = await fetch(baseURL + '/led?action=' + action);
                if (response.ok) {
                    console.log('LED:', action);
                }
            } catch (err) {
                console.error('LED error:', err);
            }
        }
        
        // Send servo command
        async function sendServo(position) {
            servoSlider.value = position;
            updateServoDisplay(position);
            try {
                const response = await fetch(baseURL + '/servo?position=' + position);
                if (response.ok) {
                    console.log('Servo:', position);
                }
            } catch (err) {
                console.error('Servo error:', err);
            }
        }
        
        // Toggle stream
        function toggleStream() {
            if (streamActive) {
                stopStream();
            } else {
                startStream();
            }
        }
        
        // Start stream
        function startStream() {
            const cacheBust = streamURL + '?cb=' + Date.now();
            streamImage.src = cacheBust;
            streamActive = true;
            streamToggle.textContent = '⏹ DETENER STREAM';
            streamStatus.textContent = 'STREAM: ONLINE';
            streamStatus.style.color = '#48bb78';
        }
        
        // Stop stream
        function stopStream() {
            window.stop();
            streamImage.src = '';
            streamActive = false;
            streamToggle.textContent = '▶ INICIAR STREAM';
            streamStatus.textContent = 'STREAM: OFFLINE';
            streamStatus.style.color = '#f56565';
        }
        
        // Check connection status
        async function checkStatus() {
            try {
                const response = await fetch(baseURL + '/');
                if (response.ok) {
                    connectionStatus.classList.add('active');
                    statusText.textContent = 'CONECTADO';
                    return true;
                }
            } catch (err) {
                connectionStatus.classList.remove('active');
                statusText.textContent = 'DESCONECTADO';
                return false;
            }
        }
        
        // Initialize
        window.onload = async function() {
            const connected = await checkStatus();
            if (connected) {
                // Auto-start stream after a short delay
                setTimeout(startStream, 500);
            }
            
            // Check status periodically
            setInterval(checkStatus, 5000);
        };
        
        // Prevent accidental page refresh on mobile
        let lastTouchEnd = 0;
        document.addEventListener('touchend', function (event) {
            const now = Date.now();
            if (now - lastTouchEnd <= 300) {
                event.preventDefault();
            }
            lastTouchEnd = now;
        }, false);
    </script>
</body>
</html>
)=====";
