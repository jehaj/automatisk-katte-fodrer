#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HX711.h>
#include <Servo.h>

// weight
HX711 scale;

// D6=12 and D5=14
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 14;

const char *ssid     = "SSID";
const char *password = "PASSWORD";

WiFiUDP ntpUPD;

// dk.pool.ntp.org
// tjekker klokken hvert andet minut (60*2*1000=120000)
NTPClient timeClient(ntpUPD, "dk.pool.ntp.org", 0, 120000);

// servo D7 = 13
Servo myServo;
const int servoPin = 13;

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

  // test servo motor movement:
  // 90 is no movement (https://www.arduino.cc/en/Reference/ServoWrite)
  // from testing i found out that the following apply to my servo motor
  // below 90 is clockwise
  // highter than 90 is counter clockwise
  myServo.attach(servoPin);
  myServo.write(80);
  delay(1500);
  myServo.write(70);
  delay(1500);
  myServo.write(100);
  delay(1500);
  myServo.write(110);
  delay(1500);
  myServo.write(90);
  
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
