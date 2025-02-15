#include "DHT.h"

#define DHTPIN 5   
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(115200);
  dht.begin();
}

void loop() 
{
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.println("°C ");
}