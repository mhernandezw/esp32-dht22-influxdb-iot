#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif
  
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "DHT.h"

// Configuración del sensor DHT22
#define DHTTYPE DHT22
#define DHTPIN 13

// --- CONFIGURACIÓN SENSIBLE (ANONIMIZADA) ---
#define WIFI_SSID "TU_SSID_WIFI"
#define WIFI_PASSWORD "TU_PASSWORD_WIFI"

#define INFLUXDB_URL "http://TU_IP_LOCAL_O_DOMINIO:PUERTO"
#define INFLUXDB_TOKEN "TU_INFLUXDB_TOKEN_AQUÍ"
#define INFLUXDB_ORG "ID_DE_TU_ORGANIZACION"
#define INFLUXDB_BUCKET "NOMBRE_DE_TU_BUCKET"

// Info de zona horaria
#define TZ_INFO "UTC2"

// Instancia del cliente InfluxDB
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Declaración del punto de datos (Measurement)
Point sensor("wifi_status");

// Configuración del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Configuración WiFi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando a WiFi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Sincronización de tiempo necesaria para InfluxDB
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Validación de conexión al servidor
  if (client.validateConnection()) {
    Serial.print("Conectado a InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("Error de conexión InfluxDB: ");
    Serial.println(client.getLastErrorMessage());
  }
  
  sensor.addTag("DispositivoESP32", DEVICE);
}

void loop() {
  // Limpiamos campos para reutilizar el punto
  sensor.clearFields();

  // Lectura de temperatura y humedad
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Verificamos si la lectura es válida
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer el sensor DHT");
    return;
  }

  // Añadimos los campos al punto
  sensor.addField("Humedad", h);
  sensor.addField("Temperatura", t);
  sensor.addField("Índice de calor", dht.computeHeatIndex(t, h, false));

  Serial.print("Escribiendo datos: ");
  Serial.println(sensor.toLineProtocol());

  // Comprobar conexión WiFi y reconectar si es necesario
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Conexión WiFi perdida");
  }

  // Escritura del punto en InfluxDB
  if (!client.writePoint(sensor)) {
    Serial.print("Error al escribir en InfluxDB: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Intervalo de envío: 10 segundos
  Serial.println("Esperando 10 segundos para la próxima lectura...");
  delay(10000);
}
