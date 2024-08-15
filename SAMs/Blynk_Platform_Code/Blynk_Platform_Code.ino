#define BLYNK_TEMPLATE_ID "TMPL..."
#define BLYNK_TEMPLATE_NAME "name"
#define BLYNK_AUTH_TOKEN "token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
double i = 0;
void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, "ssid", "password");
  timer.setInterval(1000, send);
}

void send() {
  Blynk.virtualWrite(V0, i);
  i += 0.01;
  Serial.println(i);
}

void loop() {
  Blynk.run();
  timer.run();
}