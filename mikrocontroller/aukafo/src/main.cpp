#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <HX711.h>
#include <NTPClient.h>
#include <Servo.h>
#include <WiFiUdp.h>

// weight
HX711 scale;

// D6=12 and D5=14
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 14;

HTTPClient http;

const char *ssid = "SSID";
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
  // Setup serial communication. Is not needed in release.
  Serial.begin(9600);

  // Setup wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Setup timeclient. This has to be done after connecting to a network
  timeClient.begin();

  // Setup scale.
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
  // this has to be called in loop
  timeClient.update();

  // This product is used in Denmark, which is in UTC+2 timezone
  String utcTime = timeClient.getFormattedTime();
  int hh = utcTime.substring(0, 2).toInt();
  int mm = utcTime.substring(3, 5).toInt();
  int ss = utcTime.substring(6, 8).toInt();
  hh += 2;
  String localTime = String(hh) + ':' + String(mm) + ':' + String(ss);
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

  // Post request to server with weight value in body
  http.begin("http://127.0.0.1:8080/weight");
  http.addHeader("Content-Type", "application/json");
  int returnCode = http.POST("");
  if (returnCode > 0) {
    Serial.println("Successfully added weight to database.");
  } else {
    Serial.println("Failed to add weight to database.\nMaybe the server is turned off?");
  }

  // Update the settings every 30 seconds
}
