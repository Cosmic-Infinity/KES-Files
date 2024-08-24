#include "DHT.h"

#define BLYNK_TEMPLATE_ID "TMPL****"
#define BLYNK_TEMPLATE_NAME "SA****"
#define BLYNK_AUTH_TOKEN "YmB9k****"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
DHT dht(D4, DHT11);
float humd, temp, indx, mois;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, "ssid", "password");
  timer.setInterval(2000, send);
  dht.begin();
}

void loop() {
  Blynk.run();
  timer.run();
  humd = dht.readHumidity();
  temp = dht.readTemperature();
  indx = dht.computeHeatIndex(temp, humd);
  mois = (100 - ((analogRead(A0) / 1023.00) * 100));
}

void send() {

  Blynk.virtualWrite(V0, humd);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, indx);
  Blynk.virtualWrite(V3, mois);

  Serial.print("Humidity (%): ");
  Serial.println((float)humd, 2);
  Serial.print("Temperature  (C): ");
  Serial.println((float)temp, 2);
  Serial.print("Feels like (Heat Index) (C) : ");
  Serial.println((float)indx, 2);
  Serial.print("Soil Moisture (%) = ");
  Serial.println((float)mois, 2);

  Serial.println("Sent to Cloud");
  Serial.print("\n\n");
}