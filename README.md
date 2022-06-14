# vems-gg-project2

Arduino

Refer to this tutorial : https://circuitdigest.com/microcontroller-projects/sending-temperature-and-humidity-data-to-firebase-database-using-esp8266

ESP8266 Board Version 2.5.1

Replace WiFi SSID and WiFi Password with yours as stated in code

Firebase libraries : https://github.com/FirebaseExtended/firebase-arduino

Update "..\Arduino\libraries\firebase-arduino-master/src/FirebaseHttpClient.h" for "static const char kFirebaseFingerprint[]" value every 2-3 months in https://www.grc.com/fingerprints.htm
in the search box, type in "test.firebaseio.com" and replace the "Security Certificate's Authentic Fingerprint" in FirebaseHttpClient.h file stated above
FIREBASE_HOST = remove http from real-time db
FIREBASE_AUTH = get from Firebase Console in Project Settings > Service Accounts > Database secrets > Show
Other libraries required : DHT, ESP8266 WiFi
