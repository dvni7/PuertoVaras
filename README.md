Conectaste el cable Ethernet (LAN de la universidad) al puerto WAN/LAN del TP-Link MR3020.
El router en modo 3G/4G

Desde el computador, ya conectado a la red del router:   "TP-Link_3B8E","91131812"
Accede a 192.168.1.1

Dentro de la plataforma el usuario y contraseña es "adminMaker"
- Ingresar a  Quick Setup
- Seleccionar region horaria Santiago
- Wireless Router Mode
- Dynamic IP (Auto Detect)
- Do NOT clone MAC Address
- Configuración de la nueva red Wi-Fi
	•	Creaste tu red privada:
	•	SSID: TP-Link_3B8E
	•	Seguridad: WPA2-Personal
	•	Contraseña:  91131812 (o la que elegiste).
	•	Le diste Finish, y el router se reinició con la nueva configuración.

	Tu Mac se conectó a la nueva red Wi-Fi del TP-Link.
	•	Tus ESP32 también se conectaron con el mismo SSID y contraseña.
	•	Ahora todos comparten una red privada (rango 192.168.0.x).

Ahora en Serial Monitor al conectar tu esp-32 te mostrará algo como " IP address: 192.168.1.101"
Copia esa Ip en el navegador para acceder a la cámara e interfaz de esa Esp
