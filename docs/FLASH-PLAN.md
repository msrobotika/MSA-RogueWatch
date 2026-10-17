# Plan de carga en COM4

1. Confirmar que `COM4` pertenece a la placa autorizada.
2. Guardar una lectura completa de 4 MiB y calcular SHA-256.
3. Compilar el firmware RogueWatch con el perfil de pantalla correcto.
4. Cargar únicamente bootloader, tabla de particiones y aplicación del proyecto.
5. Reiniciar y comprobar pantalla, botón BOOT, escaneo pasivo y consola UART.
6. Si falla, restaurar `original.bin` y comprobar el hash.

No se ejecutarán comandos de borrado total ni se habilitará inyección de paquetes.
