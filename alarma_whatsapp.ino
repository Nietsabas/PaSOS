//Enviar un mensaje de WhatsApp desde ESP32
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SAMSUNG";
const char* password = "99009988";
// COLOCAMOS EL TOKEN QUE NOS ENTREGA META
String token = "Bearer EAAEG6VGltDEBAKISy1ZAZAQ9sbS0VLgBWd9BrArs5efjIJo4jZBdjtnbtcG9lZA9KjGj83rZA8GLGgfoirlXcjGyAb5trQguUZB8kBLljKWN7JcERGCZAkfaXIcekWtrjq8KsAXMwfmi8iuhHZBP5FAVoTm34QMx8RfuaGVrRp34hua9Tp0TmvBZAK1aODvD9i32sw3pwLJXSjQZDZD";
// COLOCAMOS LA URL A DONDE SE ENVIAN LOS MENSAJES DE WHATSAPP
String servidor = "https://graph.facebook.com/v17.0/101465853032420/messages";
// CREAMOS EL JSON CON EL CONTENIDO DEL MENSAJE
String payload = "{ \"messaging_product\": \"whatsapp\", \"to\": \"56967362651\", \"type\":\"text\",\"text\": {\"body\": \"Tu persona cercana ha sufrido una caida\"}}";

// Declaramos el pin del zumbador
int pinZumbador = 15;
// Inicializamos las variables de la salida PWM
int canal = 0, resolucion = 8;
// Pin del botón
int pinBoton = 18;
// Frecuencias
int frec1 = 784;
int frec2 = 1568;

// Variable para almacenar el estado del zumbador
bool zumbadorEncendido = false;

void setup() {
  Serial.begin(115200);
  // Inicializamos la salida PWM
  ledcSetup(canal, frec1, resolucion);
  // Declaramos el pin donde se conecta el zumbador
  ledcAttachPin(pinZumbador, canal);
  // Configuramos el pin del botón como entrada con pull-up interno
  pinMode(pinBoton, INPUT_PULLUP);
  
  // COLOCAMOS USUARIO Y CONTRASEÑA DE NUESTRA RED WIFI
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Se ha conectado al wifi con la ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int buttonState = digitalRead(pinBoton); // Leemos el estado del botón

  if (Serial.available()) {
    char input = Serial.read(); // Leemos el dato ingresado por el puerto serial

    if (input == '1') {
      Serial.println("La persona se cayó. Iniciando alarma");
      
      if (WiFi.status() == WL_CONNECTED) {
        // INICIAMOS EL OBJETO HTTP QUE POSTERIORMENTE ENVIARÁ EL MENSAJE
        HTTPClient http;
        // COLOCAMOS LA URL DEL SERVIDOR A DONDE SE ENVIARÁ EL MENSAJE
        http.begin(servidor.c_str());
        // COLOCAMOS LA CABECERA DONDE INDICAMOS QUE SERÁ TIPO JSON
        http.addHeader("Content-Type", "application/json");
        // AGREGAMOS EL TOKEN EN LA CABECERA DE LOS DATOS A ENVIAR
        http.addHeader("Authorization", token);
        // ENVIAMOS LOS DATOS VIA POST
        int httpPostCode = http.POST(payload);
        
        // SI SE LOGRARON ENVIAR LOS DATOS
        if (httpPostCode > 0) {
          // RECIBIMOS LA RESPUESTA QUE NOS ENTREGA META
          String httpResponse = http.getString();
          Serial.print("HTTP Response: ");
          Serial.println(httpResponse);
        } else {
          Serial.print("Error code: ");
          Serial.println(httpPostCode);
        }
        
        http.end();
      } else {
        Serial.println("WiFi Desconectado");
      }
      zumbadorEncendido = true;
    } else if (input == '0') {
      Serial.println("La persona no se cayó.");
      zumbadorEncendido = false;
    } 
  }

  if (zumbadorEncendido) {
    ledcWriteTone(canal, frec1);
    delay(500);
    ledcWriteTone(canal, frec2);
    delay(500);
  } else {
    // Detener el zumbador
    ledcWriteTone(canal, 0);
  }

  if (buttonState == LOW) {
    Serial.println("Botón presionado. Deteniendo alarma");
    zumbadorEncendido = false;
  }
}