
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "ArduinoJson.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
char ssid[] = "";       // put your network SSID (name)
char password[] = "";  //put your network key

WiFiClientSecure client;


void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  display.clearDisplay();
  client.setInsecure();
 
}


void loop() {

     
    if (client.connect("thevirustracker.com", 443)) {
      Serial.println("connected to thevirustracker.com...");

      String http = String("GET https://thevirustracker.com/free-api?countryTotal=IN HTTP/1.1\r\nHost: thevirustracker.com\r\nConnection: close\r\nAccept: Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n\r\n");
      client.print(http);
      Serial.println("requesting...");
      //let's wait for something to come back... only a few seconds
      unsigned long startTime = millis();
      while (millis() - startTime < 5000) {
        if (client.available()) {
          Serial.println("From Server");
          break;
        }
      }
      delay(1000);
      String jsonData = client.readStringUntil('{');
      
      jsonData = "{";
      startTime = millis();
      while (millis() - startTime < 1000) {
        if (client.available()) {
          jsonData.concat(char(client.read()));
          startTime = millis();
        }
      }
     // Serial.println(jsonData);
      client.stop();

      DynamicJsonDocument doc(10000);
      // Deserialize the JSON document
      deserializeJson(doc, jsonData);
      JsonObject countrydata_0 = doc["countrydata"][0];
      JsonObject countrydata_0_info = countrydata_0["info"];
      int cases = countrydata_0["total_cases"];
      int recovered = countrydata_0["total_recovered"]; 
      int deaths = countrydata_0["total_deaths"];
      int cases_today = countrydata_0["total_new_cases_today"]; 
      int deaths_today = countrydata_0["total_new_deaths_today"];
      
     String ca = String(cases);
     
     String de = String(deaths);
     
     String cat = String(cases_today);
     
     String dat = String(deaths_today);
     
     String ra = String(recovered);
 
     Serial.println(cases);

     display.clearDisplay();
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(5, 0);
     // Display static text
     display.println("COVID19 Tracker(IN)");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0, 10);
     // Display static text
     display.println("Cases:");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(70, 10);
     // Display static text
     display.println(ca);
     display.display();
    
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0, 20);
     // Display static text
     display.println("Deaths:");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(70, 20);
     // Display static text
     display.println(de);
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0, 30);
     // Display static text
     display.println("Cases Today:");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(90, 30);
     // Display static text
     display.println(cat);
     display.display();
     
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0, 40);
     // Display static text
     display.println("Deaths Today:");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(90, 40);
     // Display static text
     display.println(dat);
     display.display();
     
      display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0, 50);
     // Display static text
     display.println("Recovered:");
     display.display();

     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(90, 50);
     // Display static text
     display.println(ra);
     display.display();
        }
      }
 
    
