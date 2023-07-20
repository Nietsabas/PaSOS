// Declaramos el pin del zumbador
int pinZumbador = 15;
// Inicializamos las variables de la salida PWM
int canal = 0, resolucion = 8;
// Pin del botón
int pinBoton = 18;
// Frecuencias
int frec1 = 784;
int frec2 = 1568;

void setup() {
  Serial.begin(115200);
  // Inicializamos la salida PWM
  ledcSetup(canal, frec1, resolucion);
  // Declaramos el pin donde se conecta el zumbador
  ledcAttachPin(pinZumbador, canal);
  // Configuramos el pin del botón como entrada con pull-up interno
  pinMode(pinBoton, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(pinBoton); // Leemos el estado del botón

  if (buttonState == LOW) {
    Serial.println("El botón está presionado");
    int contador = 0;

    while (contador < 10) {
        ledcWriteTone(canal, frec1);
        delay(500);
        contador = contador + 1;
        ledcWriteTone(canal, frec2);
        delay(500);
        contador = contador + 1;
    }
    // Detenemos el zumbador
    ledcWriteTone(canal, 0);
  } else {
    Serial.println("El botón está suelto");
    // Detenemos el zumbador
    ledcWriteTone(canal, 0);
  }
}







