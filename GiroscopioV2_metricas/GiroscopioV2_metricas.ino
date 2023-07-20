#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <vector>
#include <cmath>

Adafruit_MPU6050 mpu;
std::vector<sensors_event_t> measurements;

void printTab()
{
  Serial.print(F("\t"));
}

void printStats(float min_val, float max_val, float average, float variance, float kurtosis, float skew)
{
  Serial.print(F("Mínimo: "));
  Serial.print(min_val); printTab();
  Serial.print(F("Máximo: "));
  Serial.print(max_val); printTab();
  Serial.print(F("Promedio: "));
  Serial.print(average); printTab();
  Serial.print(F("Varianza: "));
  Serial.print(variance); printTab();
  Serial.print(F("Curtosis: "));
  Serial.print(kurtosis); printTab();
  Serial.print(F("Sesgo: "));
  Serial.println(skew);
}

void calculateStats(const std::vector<float>& data)
{
  int num_measurements = data.size();

  float min_val = data[0];
  float max_val = data[0];
  float sum = 0.0;
  float sum_squared = 0.0;

  for (const auto& value : data) {
    min_val = min(min_val, value);
    max_val = max(max_val, value);
    sum += value;
    sum_squared += value * value;
  }

  float average = sum / num_measurements;
  float variance = (sum_squared / num_measurements) - (average * average);

  float skew = 0.0;
  float kurtosis = 0.0;

  for (const auto& value : data) {
    skew += pow(value - average, 3);
    kurtosis += pow(value - average, 4);
  }

  skew /= pow(variance, 1.5);
  kurtosis /= pow(variance, 2) - 3;

  printStats(min_val, max_val, average, variance, kurtosis, skew);
}

void printRAW()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  Serial.print(F("a[x y z] g[x y z]:t"));
  Serial.print(a.acceleration.x); printTab();
  Serial.print(a.acceleration.y); printTab();
  Serial.print(a.acceleration.z); printTab();
  Serial.print(g.gyro.x);  printTab();
  Serial.print(g.gyro.y);  printTab();
  Serial.println(g.gyro.z);

  measurements.push_back(a);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  
  while (!mpu.begin())
  {
    Serial.println(F("No se pudo encontrar el MPU6050. Verifica la conexión."));
    delay(5000);
  }
  Serial.println(F("MPU6050 iniciado correctamente."));
}

void loop()
{
  measurements.clear(); // Limpiar la lista de mediciones
  
  // Realizar mediciones durante 2 segundos
  unsigned long startTime = millis();
  while (millis() - startTime < 2000) {
    printRAW();
    delay(100);
  }

  Serial.println(F("Estadísticas para el intervalo de 2 segundos:"));

  // Obtener los datos para cada columna
  std::vector<float> axData, ayData, azData, gxData, gyData, gzData;
  for (const auto& measurement : measurements) {
    axData.push_back(measurement.acceleration.x);
    ayData.push_back(measurement.acceleration.y);
    azData.push_back(measurement.acceleration.z);
    gxData.push_back(measurement.gyro.x);
    gyData.push_back(measurement.gyro.y);
    gzData.push_back(measurement.gyro.z);
  }

  Serial.println(F("Aceleración en el eje x:"));
  calculateStats(axData);

  Serial.println(F("Aceleración en el eje y:"));
  calculateStats(ayData);

  Serial.println(F("Aceleración en el eje z:"));
  calculateStats(azData);

  Serial.println(F("Velocidad angular en el eje x:"));
  calculateStats(gxData);

  Serial.println(F("Velocidad angular en el eje y:"));
  calculateStats(gyData);

  Serial.println(F("Velocidad angular en el eje z:"));
  calculateStats(gzData);

  delay(5000);
}

