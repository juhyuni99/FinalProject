#include <Arduino.h>
#include <IBMIOTF8266.h>

// USER CODE EXAMPLE : Publish Interval. The periodic update is normally recommended.
// And this can be a good example for the user code addition
String user_html = "";
char *ssid_pfix = (char *)"IoTUltra";

unsigned long lastPublishMillis = -pubInterval;

const int trigPin = 13;
const int echoPin = 12;

const int RELAY = 15;

long duration;
float distance;

void getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.017;
}

void publishData()
{
  StaticJsonDocument<512> root;
  JsonObject data = root.createNestedObject("d");

  char buf[10];

  getDistance();

  sprintf(buf, "%2.1f", distance);

  data["distance"] = buf;
  data["valve"] = digitalRead(RELAY) ? "on" : "off";

  serializeJson(root, msgBuffer);
  client.publish(publishTopic, msgBuffer);
}

void handleUserCommand(JsonDocument *root)
{
  JsonObject d = (*root)["d"];

  if (d.containsKey("valve"))
  {
    if (strcmp(d["valve"], "on"))
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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(RELAY, OUTPUT);

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

  JsonObject meta = cfg["meta"];
  pubInterval = meta.containsKey("pubInterval") ? atoi((const char *)meta["pubInterval"]) : 0;
  lastPublishMillis = -pubInterval;

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
