#include <Arduino.h>
#include <IBMIOTF8266.h>
#include <Wire.h>
#include <SSD1306.h>
#include <DHTesp.h>

SSD1306 display(0x3c, 4, 5, GEOMETRY_128_32);

unsigned long lastPublishMillis = -pubInterval;

const int RELAY = 15;

String user_html = "";
char *ssid_pfix = (char *)"IoTdata";

#define DHTPIN 14
DHTesp dht;
float temp_f;
unsigned long lastDHTReadMillis = 0;
#define interval 2000

void gettemperature()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastDHTReadMillis >= interval)
  {
    lastDHTReadMillis = currentMillis;

    temp_f = dht.getTemperature(); // Read temperature as Fahrenheit
  }
}

void publishData()
{
  StaticJsonDocument<512> root;
  JsonObject data = root.createNestedObject("d");

  char dht_buf[10];

  gettemperature();

  display.setColor(BLACK);
  display.fillRect(80, 16, 100, 33);
  display.setColor(WHITE);

  sprintf(dht_buf, "%2.1f", temp_f);
  display.drawString(80, 16, dht_buf);
  data["temperature"] = dht_buf;

  display.display();

  data["mode"] = digitalRead(RELAY) ? "secure" : "daily";

  serializeJson(root, msgBuffer);
  client.publish(publishTopic, msgBuffer);
}

void handleUserCommand(JsonDocument *root)
{
  JsonObject d = (*root)["d"];

    if (d.containsKey("mode"))
  {
    if (strcmp(d["mode"], "secure"))
    {
      digitalWrite(RELAY, LOW);
    }
    else
    {
      digitalWrite(RELAY, HIGH);
    }
    lastPublishMillis = -pubInterval;
  }
}

void message(char *topic, byte *payload, unsigned int payloadLength)
{
  byte2buff(msgBuffer, payload, payloadLength);
  StaticJsonDocument<512> root;
  DeserializationError error = deserializeJson(root, String(msgBuffer));

  if (error)
  {
    Serial.println("handleCommand: payload parse FAILED");
    return;
  }

  handleIOTCommand(topic, &root);

  if (!strcmp(updateTopic, topic))
  {
  }
  else if (!strncmp(commandTopic, topic, 10))
  {
    handleUserCommand(&root);
  }
}

void setup()
{
  Serial.begin(115200);

  dht.setup(DHTPIN, DHTesp::DHT22);

  pinMode(RELAY, OUTPUT);

  display.init();
  display.flipScreenVertically();
  display.drawString(30, 5, "IoT Thermostat");
  display.drawString(30, 16, "Current");

  initDevice();

  WiFi.mode(WIFI_STA);
  WiFi.begin((const char *)cfg["ssid"], (const char *)cfg["w_pw"]);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // main setup
  Serial.printf("\nIP address : ");
  Serial.println(WiFi.localIP());
  // USER CODE EXAMPLE : meta data to local variable
  JsonObject meta = cfg["meta"];
  pubInterval = meta.containsKey("pubInterval") ? atoi((const char *)meta["pubInterval"]) : 0;
  lastPublishMillis = -pubInterval;
  // USER CODE EXAMPLE

  set_iot_server();
  client.setCallback(message);
  iot_connect();
}

void loop()
{

  if (!client.connected())
  {
    iot_connect();
  }

  client.loop();
  if ((pubInterval != 0) && (millis() - lastPublishMillis > pubInterval))
  {
    publishData();
    lastPublishMillis = millis();
  }
}
