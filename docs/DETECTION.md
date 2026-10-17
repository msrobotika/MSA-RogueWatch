# Modelo de detección

Una red se representa con `ssid`, `bssid`, canal, tipo de seguridad y primera/última observación. La huella de confianza se crea manualmente o a partir de una red que el usuario confirma.

Se genera una alerta cuando:

```text
ssid conocido + bssid desconocido       -> posible clon
ssid conocido + seguridad más débil     -> configuración sospechosa
ssid conocido + canal inesperado         -> revisar
ssid nuevo + señal muy fuerte            -> investigar antes de conectar
```

Las decisiones se muestran con nivel `info`, `warning` o `critical` y se guardan junto con la hora, canal y RSSI.
