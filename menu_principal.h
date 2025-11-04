/*
 * Menú Principal - 3 Estilos Diferentes
 * Paleta base: Naranja/Ámbar (#FF6B35, #F7931E) + Negro (#0F0701) + Blanco
 */

// ==================== ESTILO 1: TERMINAL ====================
const char MENU_STYLE_TERMINAL[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32-CAM - Maker Campus</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Courier New', Courier, monospace;
            background: #0F0701;
            color: #FF6B35;
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }
        .terminal-container {
            max-width: 800px;
            width: 100%;
            border: 3px solid #FF6B35;
            background: rgba(15, 7, 1, 0.95);
            box-shadow: 0 0 40px rgba(255, 107, 53, 0.3);
            padding: 40px;
        }
        .header {
            border-bottom: 2px solid #FF6B35;
            padding-bottom: 20px;
            margin-bottom: 40px;
        }
        .header h1 {
            font-size: 2rem;
            letter-spacing: 0.1em;
            text-transform: uppercase;
            margin-bottom: 10px;
        }
        .header .subtitle {
            font-size: 0.9rem;
            color: #F7931E;
            letter-spacing: 0.15em;
        }
        .prompt {
            margin: 30px 0 20px;
            font-size: 0.95rem;
            letter-spacing: 0.05em;
        }
        .prompt::before {
            content: '> ';
            color: #F7931E;
            font-weight: bold;
        }
        .menu-options {
            display: flex;
            flex-direction: column;
            gap: 20px;
            margin: 30px 0;
        }
        .menu-button {
            background: rgba(255, 107, 53, 0.1);
            border: 2px solid #FF6B35;
            color: #FF6B35;
            padding: 25px 30px;
            font-family: 'Share Tech Mono', monospace;
            font-size: 1.2rem;
            letter-spacing: 0.1em;
            cursor: pointer;
            transition: all 0.3s ease;
            text-align: left;
            text-decoration: none;
            display: block;
        }
        .menu-button:hover {
            background: rgba(255, 107, 53, 0.3);
            box-shadow: 0 0 20px rgba(255, 107, 53, 0.5);
            transform: translateX(10px);
        }
        .menu-button .number {
            color: #F7931E;
            font-weight: bold;
            margin-right: 15px;
        }
        .footer {
            margin-top: 50px;
            padding-top: 20px;
            border-top: 1px solid rgba(255, 107, 53, 0.3);
            font-size: 0.75rem;
            color: #F7931E;
            text-align: center;
            letter-spacing: 0.1em;
        }
        @media (max-width: 640px) {
            .terminal-container { padding: 20px; }
            .header h1 { font-size: 1.5rem; }
            .menu-button { padding: 20px; font-size: 1rem; }
        }
    </style>
</head>
<body>
    <div class="terminal-container">
        <div class="header">
            <h1>MAKER CAMPUS</h1>
            <div class="subtitle">ESP32-CAM ROBOT SYSTEM v2.0</div>
        </div>
        
        <div class="prompt">ACCESO AL SISTEMA:</div>
        
        <div class="menu-options">
            <a href="/robot" class="menu-button">
                <span class="number">[●]</span> CONTROLAR ROBOT
            </a>
        </div>
        
        <div class="footer">
            MAKER CAMPUS © 2025 | PUERTO VARAS PROJECT
        </div>
    </div>
</body>
</html>
)=====";

// ==================== ESTILO 2: MODERN CARDS ====================
const char MENU_STYLE_MODERN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32-CAM - Maker Campus</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Arial, sans-serif;
            background: linear-gradient(135deg, #0F0701 0%, #1a0f05 50%, #0F0701 100%);
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding: 20px;
            position: relative;
            overflow: hidden;
        }
        body::before {
            content: '';
            position: absolute;
            top: -50%;
            left: -50%;
            width: 200%;
            height: 200%;
            background: radial-gradient(circle, rgba(255, 107, 53, 0.1) 0%, transparent 70%);
            animation: pulse 8s ease-in-out infinite;
        }
        @keyframes pulse {
            0%, 100% { transform: scale(1); opacity: 0.3; }
            50% { transform: scale(1.1); opacity: 0.5; }
        }
        .container {
            max-width: 1000px;
            width: 100%;
            position: relative;
            z-index: 1;
        }
        .header {
            text-align: center;
            margin-bottom: 60px;
            color: white;
        }
        .header h1 {
            font-size: 3rem;
            font-weight: 700;
            background: linear-gradient(135deg, #FF6B35 0%, #F7931E 100%);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            margin-bottom: 15px;
            letter-spacing: 0.05em;
        }
        .header .subtitle {
            font-size: 1.1rem;
            color: #F7931E;
            font-weight: 400;
            letter-spacing: 0.1em;
        }
        .cards-container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
            gap: 30px;
            margin-bottom: 40px;
        }
        .card {
            background: rgba(255, 255, 255, 0.05);
            backdrop-filter: blur(10px);
            border: 2px solid rgba(255, 107, 53, 0.3);
            border-radius: 20px;
            padding: 40px;
            text-decoration: none;
            color: white;
            transition: all 0.4s ease;
            position: relative;
            overflow: hidden;
        }
        .card::before {
            content: '';
            position: absolute;
            top: 0;
            left: -100%;
            width: 100%;
            height: 100%;
            background: linear-gradient(90deg, transparent, rgba(255, 107, 53, 0.2), transparent);
            transition: left 0.5s ease;
        }
        .card:hover::before {
            left: 100%;
        }
        .card:hover {
            border-color: #FF6B35;
            box-shadow: 0 20px 60px rgba(255, 107, 53, 0.4);
            transform: translateY(-10px);
        }
        .card-icon {
            font-size: 4rem;
            margin-bottom: 20px;
            display: block;
        }
        .card-title {
            font-size: 1.5rem;
            font-weight: 600;
            margin-bottom: 15px;
            color: #FF6B35;
        }
        .card-description {
            font-size: 0.95rem;
            color: rgba(255, 255, 255, 0.7);
            line-height: 1.6;
        }
        .footer {
            text-align: center;
            color: #F7931E;
            font-size: 0.85rem;
            margin-top: 40px;
            letter-spacing: 0.05em;
        }
        @media (max-width: 768px) {
            .header h1 { font-size: 2rem; }
            .cards-container { grid-template-columns: 1fr; gap: 20px; }
            .card { padding: 30px; }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>MAKER CAMPUS</h1>
            <div class="subtitle">ESP32-CAM Robot System</div>
        </div>
        
        <div class="cards-container">
            <a href="/robot" class="card">
                <span class="card-icon">🤖</span>
                <div class="card-title">Controlar Robot</div>
                <div class="card-description">
                    Interfaz completa de control con streaming en vivo,
                    navegación y control de cámara.
                </div>
            </a>
        </div>
        
        <div class="footer">
            MAKER CAMPUS © 2025 | Puerto Varas Project
        </div>
    </div>
</body>
</html>
)=====";

// ==================== ESTILO 3: MAKER CAMPUS BRANDING ====================
const char MENU_STYLE_CAMPUS[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32-CAM - Maker Campus</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: Impact, 'Arial Black', Arial, sans-serif;
            background: #0F0701;
            color: white;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
            padding: 20px;
        }
        .top-bar {
            background: linear-gradient(90deg, #FF6B35 0%, #F7931E 100%);
            padding: 5px 0;
            text-align: center;
            font-size: 0.75rem;
            letter-spacing: 0.2em;
            font-weight: 700;
            color: #0F0701;
            margin: -20px -20px 20px -20px;
        }
        .main-container {
            flex: 1;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            max-width: 900px;
            width: 100%;
            margin: 0 auto;
        }
        .logo-section {
            text-align: center;
            margin-bottom: 60px;
        }
        .logo-section h1 {
            font-size: 3.5rem;
            font-weight: 900;
            background: linear-gradient(135deg, #FF6B35 0%, #F7931E 50%, #FF6B35 100%);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            margin-bottom: 10px;
            letter-spacing: 0.05em;
            text-transform: uppercase;
        }
        .logo-section .tagline {
            font-size: 1rem;
            color: #F7931E;
            letter-spacing: 0.3em;
            font-weight: 400;
        }
        .divider {
            width: 100px;
            height: 3px;
            background: linear-gradient(90deg, transparent, #FF6B35, transparent);
            margin: 30px auto;
        }
        .options-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
            gap: 25px;
            width: 100%;
            margin-bottom: 40px;
        }
        .option-card {
            background: rgba(255, 107, 53, 0.05);
            border: 3px solid #FF6B35;
            border-radius: 15px;
            padding: 40px 30px;
            text-decoration: none;
            color: white;
            display: flex;
            flex-direction: column;
            align-items: center;
            text-align: center;
            transition: all 0.3s ease;
            position: relative;
            overflow: hidden;
        }
        .option-card::after {
            content: '';
            position: absolute;
            bottom: 0;
            left: 0;
            width: 100%;
            height: 0;
            background: linear-gradient(180deg, transparent, rgba(255, 107, 53, 0.3));
            transition: height 0.3s ease;
        }
        .option-card:hover::after {
            height: 100%;
        }
        .option-card:hover {
            border-color: #F7931E;
            box-shadow: 0 0 40px rgba(255, 107, 53, 0.6);
            transform: scale(1.05);
        }
        .option-icon {
            font-size: 5rem;
            margin-bottom: 20px;
            position: relative;
            z-index: 1;
        }
        .option-title {
            font-size: 1.3rem;
            font-weight: 700;
            color: #FF6B35;
            margin-bottom: 15px;
            text-transform: uppercase;
            letter-spacing: 0.1em;
            position: relative;
            z-index: 1;
        }
        .option-desc {
            font-size: 0.85rem;
            color: rgba(255, 255, 255, 0.8);
            line-height: 1.6;
            font-weight: 400;
            position: relative;
            z-index: 1;
        }
        .info-panel {
            background: rgba(247, 147, 30, 0.1);
            border: 1px solid rgba(247, 147, 30, 0.3);
            border-radius: 10px;
            padding: 20px;
            text-align: center;
            font-size: 0.85rem;
            color: #F7931E;
            letter-spacing: 0.05em;
        }
        .info-panel strong {
            color: #FF6B35;
        }
        @media (max-width: 768px) {
            .logo-section h1 { font-size: 2.5rem; }
            .options-grid { grid-template-columns: 1fr; }
        }
    </style>
</head>
<body>
    <div class="top-bar">MAKER CAMPUS - PUERTO VARAS</div>
    
    <div class="main-container">
        <div class="logo-section">
            <h1>MAKER CAMPUS</h1>
            <div class="tagline">Exploradores del Universo</div>
        </div>
        
        <div class="divider"></div>
        
        <div class="options-grid">
            <a href="/robot" class="option-card">
                <div class="option-icon">🎮</div>
                <div class="option-title">Controlar</div>
                <div class="option-desc">
                    Control completo del robot con video en vivo
                </div>
            </a>
        </div>
        
        <div class="info-panel">
            <strong>Maker Campus</strong> | Puerto Varas Project 
        </div>
    </div>
</body>
</html>
)=====";
