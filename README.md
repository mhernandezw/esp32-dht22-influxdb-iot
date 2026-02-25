# 🌡️ IoT Sensor Node: Monitorización Ambiental con ESP32 e InfluxDB

Este proyecto consiste en un nodo sensor IoT diseñado para la recolección de métricas de temperatura y humedad en tiempo real. Los datos son enviados a una base de datos de series temporales (**InfluxDB**) alojada en un clúster local de **MicroK8s**, sirviendo como fuente de datos para dashboards de Grafana y agentes de IA.

---

## 🚀 Características Técnicas
- **Protocolo:** Comunicación mediante HTTP API v2 de InfluxDB.
- **Seguridad:** Uso de tokens de autenticación y anonimización de red.
- **Precisión:** Sensor DHT22 para lecturas estables de temperatura y humedad.
- **Sincronización:** Implementación de NTP (Network Time Protocol) para garantizar que los timestamps de las métricas sean exactos.

## 🛠️ Requisitos y Materiales

### 1. Hardware
- **Microcontrolador:** ESP32 (compatible con ESP8266).
- **Sensor:** DHT22 (AM2302).
- **Infraestructura:** Mini PC ejecutando **MicroK8s** (Backend).

### 2. Librerías Necesarias (Arduino IDE)
Para compilar este proyecto, debes instalar las siguientes librerías desde el Gestor de Librerías:
1. **ESP32 InfluxDB Client** (por Tobias Schürg).
2. **DHT sensor library** (por Adafruit).
3. **Adafruit Unified Sensor**.

---

## 📂 Estructura del Proyecto
- `esp32_sensor.ino`: Código fuente principal para el microcontrolador.
- **Ecosistema:** Este repositorio alimenta el [Dashboard de Grafana](http://rubius.ddns.net/public-dashboards/304227f5af52407482bd83fd15766d8f?orgId=1&refresh=10s) y el [Agente de IA](https://github.com/TU_USUARIO/ai-agent-influxdb-weather).

## ⚙️ Configuración del Código
Para desplegar este código en tu propio entorno, asegúrate de actualizar los *placeholders* en el archivo `.ino`:
- `WIFI_SSID` y `WIFI_PASSWORD`.
- `INFLUXDB_URL`, `INFLUXDB_TOKEN`, `INFLUXDB_ORG` y `INFLUXDB_BUCKET`.

---

👤 **Marcelo Carlos Hernandez Wrona**
- **Sistemas:** Administrador de Sistemas con más de 10 años de experiencia.
- **Formación:** Grado Superior ASIR y Máster en IA (Founderz).
- 📧 [marcelo_hernandez_12@hotmail.com](mailto:marcelo_hernandez_12@hotmail.com)
