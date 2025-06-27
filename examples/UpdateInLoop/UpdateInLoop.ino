#include <DTF_ESP8266Update.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

// You must uncomment the following 4 lines and set each one to appropriate values for your project

// #define WIFI_SSID       "" // The name of your WiFi network
// #define WIFI_PASSWORD   "" // Your WiFi network password
// #define DTF_PRODUCT_ID  "" // Your product id from the Deploy the Fleet settings
// String CURRENT_VERSION = ""; // The version of this firmware to be sent to Deploy the Fleet for update decisioning

#ifndef WIFI_SSID
#error You must define WIFI_SSID and WIFI_PASSWORD
#endif

#ifndef DTF_PRODUCT_ID
#error You must provide your Deploy the Fleet product id in the DTF_PRODUCT_ID define at the top of the file
#endif

ESP8266WiFiMulti WiFiMulti;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("Deploy the Fleet ESP8266 Update Example");

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  // This static variable ensures that the loop function will only check for updates
  // a single time after boot.
  static bool checkedForUpdates = false;

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
      if (!checkedForUpdates)
      {
        checkedForUpdates = true; // don't check for updates again
        DTF_ESP8266Update::getFirmwareUpdate(DTF_PRODUCT_ID, CURRENT_VERSION.c_str());
      }
    Serial.println("This is version " + CURRENT_VERSION);
    delay(5000);
  }
}