# Guía rápida: ESP32-CAM en modo Robot Access Point

Esta versión del proyecto convierte a la ESP32-CAM en un punto de acceso Wi-Fi propio y expone una interfaz para controlar el robot. Sigue estos pasos cada vez que prepares un dispositivo.

## 1. Configura el firmware

1. Abre `esp32-cam-webserver/myconfig.h`.
2. Ajusta las credenciales del punto de acceso en `stationList[0]`.  
   ```cpp
   {"ESP32-CAM-PV", "cambia_esta_clave", true}
   ```  
   - Cambia el SSID y la contraseña por valores seguros (mínimo 8 caracteres).
   - Si necesitas cambiar la IP del AP, descomenta y edita `#define AP_ADDRESS ...`.
3. (Opcional) Ajusta los `#define ROBOT_*` para invertir motores según tu cableado.

## 2. Compila y sube el sketch

1. Abre `esp32-cam-webserver/esp32-cam-webserver.ino` en tu IDE (Arduino IDE o PlatformIO).
2. Selecciona la placa **AI Thinker ESP32-CAM** y el puerto serie correcto.
3. Carga el firmware en la ESP32-CAM.  
   Al finalizar, reinicia la placa; el AP se levantará con el SSID definido en el paso anterior.

## 3. Conéctate al Wi-Fi del robot

1. Desde tu computador o teléfono, busca la red Wi-Fi de la ESP32-CAM (por defecto `ESP32-CAM-PV`).
2. Conéctate usando la contraseña configurada.
3. La ESP32-CAM entrega IPs en el rango `192.168.4.x`. El dispositivo pasará a ser tu gateway mientras dure la sesión.

## 4. Accede a la interfaz web

1. Abre un navegador y visita `http://192.168.4.1/`.  
   - Si definiste `URL_HOSTNAME`, puedes usar `http://<hostname>/`.
2. La portada muestra el stream de la cámara. Para controlar el robot, haz clic en **Robot Control** (también accesible vía `http://192.168.4.1/project`).
3. Verifica que:
   - El stream de video cargue correctamente.
   - Los indicadores de telemetría cambien al mover el robot (posición, heading, estado).

## 5. Controla el robot

1. Usa los botones de **Move** para avanzar (`Forward`), retroceder (`Backward`) o detener (`Stop`).
2. Los botones **Turn Left/Right** rotan sobre su eje. Si la dirección es inversa, revisa los `#define ROBOT_*_INVERTED` en `myconfig.h`.
3. Los controles de inclinación (`Tilt Up/Down`) mueven el servo definido por `CAMERA_TILT_SERVO_PIN`.
4. Cada acción se refleja en el log serie; es útil mantener un monitor abierto mientras pruebas.

## 6. Tips y solución de problemas

- Si la página no carga, confirma que sigues conectado al Wi-Fi del robot y que la ESP32-CAM recibió alimentación después de cargar el sketch.
- Para cambiar la red/clave del AP, modifica `myconfig.h`, vuelve a compilar y sube el firmware.
- El navegador puede tardar unos segundos en recibir el stream tras reiniciar la placa; recarga la página si queda en blanco.
- Cuando termines, desconéctate manualmente de la red del robot para volver a tu Wi-Fi habitual.

Con esto deberías tener la cámara y el control del robot funcionando con la ESP32-CAM como punto de acceso autónomo.
