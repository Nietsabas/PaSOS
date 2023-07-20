Claro, aquí tienes los README.md para cada uno de los códigos:

## ambulanciaV1.ino

### Descripción
Este código es para un sistema de alarma que utiliza un botón para simular una llamada de emergencia, activando una alarma sonora. La alarma se detiene cuando el botón es liberado.

### Hardware Requerido
- Placa Arduino compatible (p. ej. ESP32)
- Zumbador (buzzer) conectado al pin 15
- Botón conectado al pin 18

### Cómo utilizar
1. Conecta el zumbador al pin 15 y el botón al pin 18.
2. Sube el código a la placa Arduino.
3. Una vez cargado, el programa esperará hasta que el botón sea presionado.
4. Cuando se presione el botón, la alarma sonará con dos frecuencias alternas durante 10 ciclos.
5. La alarma se detendrá cuando se libere el botón.

---

## GiroscopioV3_metricas.ino

### Descripción
Este código utiliza un MPU6050 (giroscopio y acelerómetro) para realizar mediciones durante 2 segundos y luego calcular algunas estadísticas básicas sobre los datos recopilados. Las estadísticas incluyen el valor mínimo, máximo, promedio, varianza, curtosis y sesgo.

### Hardware Requerido
- Placa Arduino compatible (p. ej. ESP32)
- MPU6050 (giroscopio y acelerómetro) conectado al bus I2C de la placa

### Cómo utilizar
1. Conecta el MPU6050 al bus I2C de la placa Arduino.
2. Sube el código a la placa Arduino.
3. Una vez cargado, el programa recopilará datos del MPU6050 durante 2 segundos.
4. Luego calculará y mostrará las estadísticas para la aceleración en los ejes x, y, z y para la velocidad angular en los ejes x, y, z.

---

## alarma_whatsapp.ino

### Descripción
Este código activa una alarma sonora utilizando un zumbador (buzzer) cuando recibe una señal a través del puerto serie. Además, envía un mensaje de WhatsApp utilizando la API de Facebook Graph al recibir el número '1' por el puerto serie.

### Hardware Requerido
- Placa Arduino compatible (p. ej. ESP32)
- Zumbador (buzzer) conectado al pin 15
- Botón conectado al pin 18 (opcional, utilizado para detener la alarma manualmente)
- Conexión a Internet (WiFi)

### Cómo utilizar
1. Conecta el zumbador al pin 15 y el botón al pin 18 (opcional).
2. Asegúrate de tener una conexión WiFi válida y cambia los valores de la red WiFi en el código.
3. Sube el código a la placa Arduino.
4. Una vez cargado, el programa estará a la espera de una señal por el puerto serie:
   - Al recibir '1', activará la alarma sonora y enviará un mensaje de WhatsApp.
   - Al recibir '0', detendrá la alarma sonora.