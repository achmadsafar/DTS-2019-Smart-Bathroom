/***
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
***/

#include <WiFi.h>
#include <PubSubClient.h>
#include <NewPing.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "aaa";
const char* password = "korekapi456";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "192.168.43.107";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];


// inisiasi ultrasonic sensor
#define TRIGGERPIN 33
#define ECHOPIN 35
#define MAXDISTANCE 400
#define led1  26
#define led2  27
unsigned int distance;
NewPing sonar (TRIGGERPIN, ECHOPIN, MAXDISTANCE);

// LM35 Pin
const int lm35 = 32;
int value;
int temp;
int terpakai;
int sisavolume;

void setup() {
  Serial.begin(115200);
  // default settings

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(lm35, INPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Device data received : ");
    Serial.println(messageTemp);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/lm35sensor");
      client.subscribe("esp32/ultrasonic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    publishultrasonic();
    publishsuhu();
  }
}

void publishultrasonic()
{
    delay(1000);
    distance = sonar.ping_cm();
    terpakai = distance *15;
    sisavolume = 120 - terpakai;
    Serial.print(sisavolume);
    Serial.println("cm3");
    char ultrasonicString[8];
    dtostrf(sisavolume,1,2, ultrasonicString);
    String payloadultrasonicStr = buildJson2();
    char payload1[payloadultrasonicStr.length()+1];
    payloadultrasonicStr.toCharArray(payload1, payloadultrasonicStr.length()+1);
    Serial.println("Sending payload1: ");
    Serial.println(payload1);
    client.publish("esp32/ultrasonic", payload1);
  }
void publishsuhu()
{
    temp = analogRead(lm35);
    value = map(temp, 0, 4095, 2, 150);
    if(value < 25)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      } else if(value > 25)
      {
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        }
    // Convert the value to a char array
    char suhuString[8];
    dtostrf(value, 1, 2, suhuString);
    Serial.print("suhu: ");
    Serial.println(suhuString);
    String payloadStr = buildJson1();
    char payload[payloadStr.length()+1];
    payloadStr.toCharArray(payload, payloadStr.length()+1);
    Serial.println("Sending payload: ");
    Serial.println(payload);
    client.publish("esp32/lm35sensor", payload);
  }

String buildJson2() {
  String data;
  data += (int)sisavolume;
  return data;
}

String buildJson1() {
  String data;
  data += (int)value;
  return data;
}
