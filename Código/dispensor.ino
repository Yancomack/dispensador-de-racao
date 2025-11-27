#include <WiFi.h>
#include <PubSubClient.h>
#include "HX711.h"
#include <Servo.h>
#include <ArduinoJson.h>

const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
const char* mqtt_server = "IP_DO_BROKER";

#define DOUT  4
#define CLK   5
#define SERVO_PIN  9

HX711 scale;
Servo servo;

float pesoInicial;
float pesoPrimeiraDose;
float pesoSegundaDose;


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");

  client.setServer(mqtt_server, 1883);
  
  scale.begin(DOUT, CLK);
  scale.set_scale(2280.f); // ajuste conforme sua célula
  scale.tare();

  servo.attach(SERVO_PIN, 600, 2400);
  servo.write(0); // posição inicial
  delay(1000);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  pesoInicial = scale.get_units(10);
  Serial.print("Peso Inicial: ");
  Serial.println(pesoInicial);
  
  liberarRacao();
  delay(10000); 
  pesoPrimeiraDose = scale.get_units(10);
  Serial.print("Peso após primeira dose: ");
  Serial.println(pesoPrimeiraDose);

  liberarRacao();
  delay(10000);
  pesoSegundaDose = scale.get_units(10);
  Serial.print("Peso após segunda dose: ");
  Serial.println(pesoSegundaDose);
  
  StaticJsonDocument<256> doc;
  doc["Horario"] = getTimestamp();
  doc["Peso inicial"] = pesoInicial;
  doc["Peso após primeira refeição"] = pesoPrimeiraDose;
  doc["Peso após segunda refeição"] = pesoSegundaDose;

  char buffer[256];
  serializeJson(doc, buffer);
  Serial.println(buffer);

  client.publish("dispenser/pesos", buffer);


  delay(24 * 60 * 60 * 1000); 
}

void liberarRacao() {
  servo.write(50);
  delay(1000);
  servo.write(20); 
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32_Dispenser")) {
      Serial.println("conectado");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo em 10 segundos");
      delay(10000);
    }
  }
}

String getTimestamp() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "00:00:00";
  }
  char buf[20];
  strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buf);
}
