/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <NewPing.h>

#define TRIGGERPIN 25
#define ECHOPIN 26
#define MAXDISTANCE 400

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "vA4-4JYK3VXO2pSb4tXMLkBiaFuQOEvD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "aaa";
char pass[] = "korekapi456";

NewPing sonar(TRIGGERPIN, ECHOPIN, MAXDISTANCE);

uint8_t wire1 = 33 ;
uint8_t wire2 = 15 ;
uint8_t wire3 = 32 ;
uint8_t wire4 = 14 ;

const uint16_t _delay = 1;
void sequence(bool a, bool b, bool c, bool d)
{
  digitalWrite(wire1, a);
  digitalWrite(wire2, b);
  digitalWrite(wire3, c);
  digitalWrite(wire4, d);
  delay(_delay);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(wire1, OUTPUT);
  pinMode(wire2, OUTPUT);
  pinMode(wire3, OUTPUT);
  pinMode(wire4, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V3)
{
  if(param.asInt()==1)
  {
  for (int i=0; i<115; i++)
    {
      sequence(HIGH, LOW, LOW, LOW);
      sequence(HIGH, HIGH, LOW, LOW);
      sequence(LOW, HIGH, LOW, LOW);
      sequence(LOW, HIGH, HIGH, LOW);
      sequence(LOW, LOW, HIGH, LOW);
      sequence(LOW, LOW, HIGH, HIGH);
      sequence(LOW, LOW, LOW, HIGH);
      sequence(HIGH, LOW, LOW, HIGH);
      
    }
  }
  else if(param.asInt()==0)
  {
    for(int j=0; j<115; j++)
    {
      sequence(LOW, LOW, LOW, HIGH);
      sequence(LOW, LOW, HIGH, HIGH);
      sequence(LOW, LOW, HIGH, LOW);
      sequence(LOW, HIGH, HIGH, LOW);
      sequence(LOW, HIGH, LOW, LOW);
      sequence(HIGH, HIGH, LOW, LOW);
      sequence(HIGH, LOW, LOW, LOW);
      sequence(HIGH, LOW, LOW, HIGH); 
    }
    }
  }

void loop()
{
  Blynk.run();
  ultrasonic();
//    } else if(Blynk.virtualWrite(3) == HIGH)
//   {
//    for(int j=0; j<125; j++)
//    {
//      sequence(LOW, LOW, LOW, HIGH);
//      sequence(LOW, LOW, HIGH, HIGH);
//      sequence(LOW, LOW, HIGH, LOW);
//      sequence(LOW, HIGH, HIGH, LOW);
//      sequence(LOW, HIGH, LOW, LOW);
//      sequence(HIGH, HIGH, LOW, LOW);
//      sequence(HIGH, LOW, LOW, LOW);
//      sequence(HIGH, LOW, LOW, HIGH); 
//    }
//   }
}

void ultrasonic()
{
    delay(1000);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  if (distance == 10)
  {
        for(int j=0; j<115; j++)
    {
      sequence(LOW, LOW, LOW, HIGH);
      sequence(LOW, LOW, HIGH, HIGH);
      sequence(LOW, LOW, HIGH, LOW);
      sequence(LOW, HIGH, HIGH, LOW);
      sequence(LOW, HIGH, LOW, LOW);
      sequence(HIGH, HIGH, LOW, LOW);
      sequence(HIGH, LOW, LOW, LOW);
      sequence(HIGH, LOW, LOW, HIGH); 
    }  
    } else if (distance == 15)
    {
      for(int j=0; j<115; j++)
      {
      sequence(HIGH, LOW, LOW, LOW);
      sequence(HIGH, HIGH, LOW, LOW);
      sequence(LOW, HIGH, LOW, LOW);
      sequence(LOW, HIGH, HIGH, LOW);
      sequence(LOW, LOW, HIGH, LOW);
      sequence(LOW, LOW, HIGH, HIGH);
      sequence(LOW, LOW, LOW, HIGH);
      sequence(HIGH, LOW, LOW, HIGH); 
      }
    }
  Serial.println("cm");
  delay(1000);
  }
