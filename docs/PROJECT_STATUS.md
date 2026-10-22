# MSA RogueWatch · Estado técnico

**Revisión:** 2026-10-22  
**Tipo:** prototipo ESP32 para observación pasiva y uso en redes autorizadas.

## Estructura disponible
- [Código y configuración de firmware](../firmware/)
- [Capturas de UI del prototipo](../ui/captures/radar.png)
- [Capturas de alertas](../ui/captures/alertas.png)
- [Seguridad](../SECURITY.md)
- [CI](../.github/workflows/ci.yml)

## Evidencias y límites

La galería demuestra la **interfaz de prototipo**, no una campaña reproducible de hardware ni una detección forense verificada. Las alertas sobre un SSID o BSSID son indicios, no pruebas concluyentes de actividad maliciosa.

Validación pendiente: compilación en placa específica, pruebas pasivas con datos anonimizados, exactitud de las alertas, falsas alarmas, consumo y test de pantalla. No realizar escaneo invasivo ni capturar datos de terceros sin autorización.
