# Firmware RogueWatch

Esta carpeta reservará el firmware ESP-IDF para la ESP32 clásica con pantalla ST7789.

La primera versión tendrá tres tareas separadas:

1. `scanner`: escaneo Wi-Fi pasivo (`esp_wifi_scan_start`), sin asociación ni inyección.
2. `model`: comparación de SSID/BSSID/canal/cifrado contra huellas confirmadas.
3. `display`: radar y alertas visuales; el borde rojo solo se activa con una anomalía observada.

El firmware Canary actual no se reutiliza como binario: son funciones distintas y no se sobrescribirá la placa hasta que esta implementación compile y pase las pruebas de laboratorio.
