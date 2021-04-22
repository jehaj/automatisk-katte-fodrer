#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HX711.h>

// weight
HX711 scale;

// D6=12 and D5=14
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 14;

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

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();

  String utcTime = timeClient.getFormattedTime();
  int hh = utcTime.substring(0, 2).toInt();
  int mm = utcTime.substring(3, 5).toInt();
  int ss = utcTime.substring(6, 8).toInt();
  hh += 2;
  String localTime = String(hh) +':'+ String(mm) +':'+ String(ss);
  Serial.println(localTime);

  // weight
  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
}
