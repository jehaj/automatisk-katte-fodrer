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

// D6=12 and D5=14 (D0=16)
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 14;

HTTPClient http;
const char *serverAddress = "http://192.168.223.83:8080/";
StaticJsonDocument<1024> doc;
JsonArray arr;
int numberOfSettings = 0;
unsigned long period = 1000 * 60 * 30;  // millis*seconds*minutes
unsigned long time_now = 0;

int p_mm = 0;

const char *ssid = "SSID";
const char *password = "PASSWORD";

WiFiUDP ntpUPD;

// dk.pool.ntp.org
// tjekker klokken hvert andet minut (60*2*1000=120000)
NTPClient timeClient(ntpUPD, "dk.pool.ntp.org", 0, 120000);

// servo D7 = 13
Servo myServo;
const int servoPin = 13;

int sendWeightToServer(long freading) {
  // Post request to server with weight value in body
  http.begin(String(serverAddress) + String("weight"));
  http.addHeader("Content-Type", "application/json");
  int returnCode = http.POST("{\"value\":\"" + String(freading) + "\"}");
  http.end();
  if (returnCode > 0) {
    Serial.println("Successfully added weight to database.");
  } else {
    Serial.println("Failed to add weight to database.\nMaybe the server is turned off?");
  }
  return returnCode;
}

int sendWeightToServer(long freading, int tries) {
  int returnCode = sendWeightToServer(freading);
  if (returnCode <= 0 && tries > 0) {
    Serial.println("Seems like the server did not respond. Sending again!");
    sendWeightToServer(freading, tries-1);
  }
  return returnCode;
}

void getSettingsFromServer() {
  http.begin(String(serverAddress) + String("settings"));
  int returnCode = http.GET();
  if (returnCode > 0) {
    Serial.println("Successfully received settings from server.");
    String payload = http.getString();
    DeserializationError err = deserializeJson(doc, payload);
    
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
    } else {
      arr = doc.as<JsonArray>();
    }
  } else {
    Serial.println("Server didn't answer. Maybe it's turned off?");
  }
  http.end();
}

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
  scale.set_scale(-251.f);
  scale.tare();

  // test servo motor movement:
  // 90 is no movement (https://www.arduino.cc/en/Reference/ServoWrite)
  // from testing i found out that the following apply to my servo motor
  // below 90 is clockwise
  // highter than 90 is counter clockwise
  myServo.attach(servoPin);
  // myServo.write(80);
  // delay(1500);
  // myServo.write(70);
  // delay(1500);
  // myServo.write(100);
  // delay(1500);
  // myServo.write(110);
  // delay(1500);
  // myServo.write(90);

  // get settings from the server. it checks every 30 minutes, but not in
  // the beginning. therefore the function is called below.
  getSettingsFromServer();
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
    long reading = scale.get_units();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
    sendWeightToServer(reading, 3);
  } else {
    Serial.println("HX711 not found.");
  }

  // Update the settings every 30 minutes
  // it is overflow proof
  // thanks https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
  if (millis() - time_now > period) {
    time_now = millis();
    getSettingsFromServer();
  }
  
  // loops over the settings array received from the server
  for (JsonObject repo : arr) {
    const String ntime = repo["time"];
    const int nvalue = int(repo["value"]);

    // this condition makes sure that the servo only turns on once
    if((ntime.substring(0, 2) == String(hh)) &&
       (ntime.substring(3, 5) == String(mm) && p_mm != mm)) {
        // turn on the servo. the time depends on the value from the settings.
        // a higher number means the servo will be turned on for a longe period
        // of time. this code is blocking because it uses the delay function.
         myServo.write(80);
         delay(nvalue*1000);
         myServo.write(90);
    }
  }

  // remember the the previous minute number to make sure servo
  // only turns on once
  p_mm = mm;

  delay(5000);
}
