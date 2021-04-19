#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid     = "SSID";
const char *password = "PASSWORD";

WiFiUDP ntpUPD;

// dk.pool.ntp.org
NTPClient timeClient(ntpUPD, "dk.pool.ntp.org", 0, 120000);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println();

  timeClient.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
