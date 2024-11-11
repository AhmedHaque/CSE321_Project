#include <MAX30105.h>
#include <heartRate.h>
#include <spo2_algorithm.h>
#include <Wire.h>
#include <DHT_U.h>
#define DHT22_PIN 2
#define GREEN 7
#define RED 8

DHT dht22(DHT22_PIN, DHT22);

MAX30105 heart;

const byte RATE_SIZE  = 4; 
byte rates[RATE_SIZE]; 
byte rateSpot = 0;
long lastBeat = 0; 
float beatsPerMinute;
int beatAvg;

void setup()
{ 
  dht22.begin();
  heart.begin(Wire, I2C_SPEED_FAST);
  heart.setup();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  delay(3000);

  for (int i = 0; i < 5; i++){
    delay(500);
    digitalWrite(GREEN,HIGH);
    digitalWrite(RED,LOW);
    delay(500);
    digitalWrite(RED,HIGH);
    digitalWrite(GREEN,LOW);
  }

  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);

  delay(2000);
  
  long ir = heart.getIR();
  
  if (ir > 7000){
    printf("USER DETECTED");

    int tempC = dht22.readTemperature();
    printf("Temperature: %d", tempC);

    long delta = millis()  - lastBeat;
    lastBeat  = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    printf("Heart Beat per minute: %d", beatsPerMinute);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)               
    {
      rates[rateSpot++] = (byte)beatsPerMinute; 
      rateSpot %= RATE_SIZE; 
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE  ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }

    if (((tempC < 36.5) || (tempC >= 38)) && ((beatAvg < 60) || (beatAvg > 100)))
    {
      printf("UNHEALTHY USER");
        digitalWrite(RED,HIGH);
        delay(5000);
        digitalWrite(RED,LOW);
    }else if ((tempC < 36.5) || (tempC >= 38))
    {
      printf("UNUSUAL TEMPERATURE");
      for (int i = 0; i < 5; i++){
        delay(1000);
        digitalWrite(GREEN,HIGH);
        delay(1000);
        digitalWrite(GREEN,LOW);
      }
    }else if ((beatAvg < 60) || (beatAvg > 100))
    {
      printf("UNUSUAL HEARTBEAT");
      for (int i = 0; i < 5; i++){
        delay(1000);
        digitalWrite(RED,HIGH);
        delay(1000);
        digitalWrite(RED,LOW);
      }
    }else
    {
      printf("HEALTHY USER");
      digitalWrite(GREEN,HIGH);
      delay(5000);
      digitalWrite(GREEN,LOW);
    }
  }
}