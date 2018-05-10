#include "Magellan.h"
#include "DHT.h"
#define DHTPIN 32 
Magellan magel;
char auth[]="your key"; 		//Token Key you can get from magellan platform
#define DHTTYPE DHT22
String payload;
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;  
const long interval = 2000; 

void setup() {
  dht.begin();
  Serial.begin(9600);
  magel.begin(auth);           //init Magellan LIB
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  payload="{\"Temperature\":"+String(t)+",\"Humidity\":"+String(h)+"}"; 
  magel.post(payload);                                             
  previousMillis = currentMillis;
  }
  
}
