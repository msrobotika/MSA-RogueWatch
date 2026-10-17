# Uso en la placa

RogueWatch arranca automáticamente al conectar el USB o alimentar la placa.

- **Pulsación corta de BOOT**: cambia de pantalla (`RADAR`, `ALERTAS`, `HUELLAS`, `EVIDENCIAS`).
- **Mantener BOOT 2 segundos**: pausa o reanuda el escaneo.
- **Sin pulsar**: las pantallas rotan automáticamente.

El panel instalado es un ST7789. La pantalla mostrada en esta placa no incorpora controlador táctil ni las líneas necesarias para leer toques, por lo que no se puede activar un teclado táctil mediante software. Para una futura versión táctil habría que usar una pantalla con XPT2046, CST816 o similar y cablear su bus correspondiente.

El escaneo es pasivo: no se conecta a redes, no envía inyecciones y no expulsa clientes.
