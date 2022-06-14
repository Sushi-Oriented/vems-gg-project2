#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h> // used
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <Firebase.h> // used
#include <FirebaseArduino.h> // used
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <DHT.h> // used
#include <DHT_U.h>

#define FIREBASE_HOST "vems-gg-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "lb456SVoOORSz6wVrNHYrQiMFIPAkDgbz9hpekrn"

#define WIFI_SSID "wifi_ssid_here"
#define WIFI_PASSWORD "wifi_password_here"

#define DHTPIN 2
#define DHTTYPE DHT11 // object of DHT11

DHT dht(DHTPIN, DHTTYPE); // create object with defined params

void setup() {
  Serial.begin(9600); // baud = frequency
  delay(1000); // 1 second
  
  //  WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());

  //  Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //  Read DHT11
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Read Humidity & Temperature
  Serial.print("Humidity: ");  Serial.print(h); Serial.println("%");
  Serial.print("Temperature: ");  Serial.print(t); Serial.println("°C");
  tempChecker(5000, t);

  Firebase.pushFloat("DHT11/Humidity", h);                                    
  Firebase.pushFloat("DHT11/Temperature", t);
}

void tempChecker(long duration, float t) {
  long end_time = millis() + duration;
  while (millis() < end_time) {
    if (t >= 30){
      Serial.println("----- Temperature & humidity is within danger level -----");
      return;
    }
    else {
      return;
    }
  }
}