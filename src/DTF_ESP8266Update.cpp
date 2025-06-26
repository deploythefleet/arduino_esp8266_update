#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <time.h>

#include "DTF_ESP8266Update.h"
#define DTF_DEBUG

extern const char* isrgrootx1_cert;
extern const char* cloudflare_cert;
extern const int CERT_BUNDLE_ID;

constexpr const int NTP_MAX_WAIT_TIME_IN_SECONDS = 600; // 10 minutes

const uint8_t PROGMEM dtf_fingerprint[20] = {
    0x35, 0x98, 0x83, 0x53, 0xAC, 0x0F, 0xA3, 0xA9,
    0x6D, 0xF7, 0xCA, 0x5C, 0x24, 0x70, 0x83, 0xDA,
    0x1C, 0xF0, 0x8C, 0x3E
};

void setSystemTime()
{
    configTime(0, 0, F("pool.ntp.org"), F("time.nist.gov"));

    #ifdef DTF_DEBUG
    Serial.print(F("Waiting for NTP time sync: "));
    #endif

    time_t now = time(nullptr);
    while (now < NTP_MAX_WAIT_TIME_IN_SECONDS) {
        yield();
        delay(500);
        #ifdef DTF_DEBUG
        Serial.print(F("."));
        #endif
        now = time(nullptr);
    }

    #ifdef DTF_DEBUG
    Serial.println(F(""));
    #endif
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    #ifdef DTF_DEBUG
    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
    #endif
}

void DTF_ESP8266Update::DTF_UpdateStart() {
    #ifdef DTF_DEBUG
    Serial.println(F("Callback: OTA Update Started"));
    #endif
}

void DTF_ESP8266Update::DTF_UpdateFinished() {
    #ifdef DTF_DEBUG
    Serial.println(F("Callback: OTA Update Finished Successfully"));
    #endif
}

void DTF_ESP8266Update::DTF_UpdateProgress(int _current, int _total) {
    static int last_percentage = 0;
    if (last_percentage >= 100) {
        return;
    }

    int percentage = (int)((float)_current/(float)_total * 100);

    if ((percentage >= (last_percentage + 10)) || percentage == 100) {
        last_percentage = percentage;
        #ifdef DTF_DEBUG
        Serial.print(F("+"));
        if (percentage >= 100) {
            Serial.println();
        }
        #endif
    }
}

DTF_UpdateResponse DTF_ESP8266Update::getFirmwareUpdate(
    const char* updateUrl, 
    const char* currentVersion, 
    DTF_RebootOption rebootOption,
    DTF_SetTimeOption setTime)
{
    static BearSSL::X509List x509(isrgrootx1_cert);
    static bool timeSet = false;
    
    #ifdef DTF_DEBUG
    Serial.println(F("Checking for firmware updates"));
    #endif

    // Append the certificate bundle ID to the update URL
    String url = String(updateUrl);
    url.reserve(strlen(updateUrl) + 12);
    if(url.indexOf("?") == -1)
    {
        url.concat("?cb=");
    }
    else
    {
        url.concat("&cb=");
    }
    url.concat(CERT_BUNDLE_ID);

    // Ensure the current time is set and accurate
    if (setTime == DTF_SetTimeOption::SET_TIME && !timeSet)
    {
        setSystemTime();
        timeSet = true;
    }

    if (rebootOption == DTF_RebootOption::NO_REBOOT)
    {
        ESPhttpUpdate.rebootOnUpdate(false);
    }

    // Create a secure client using the Let's Encrypt certificate
    BearSSL::WiFiClientSecure client;
    client.setTrustAnchors(&x509);
    client.setTimeout(20); // 20 second timeout

    // Callbacks setting
    ESPhttpUpdate.onStart(DTF_UpdateStart);
    ESPhttpUpdate.onEnd(DTF_UpdateFinished);
    ESPhttpUpdate.onProgress(DTF_UpdateProgress);

    // The following line invokes the update library and will send all necessary headers
    // to Deploy the Fleet for it to decision an update. Make sure the version argument
    // is always accurate as this is used to determine if a device needs an update or not.
    // Get the URL from your product dashboard in Deploy the Fleet
    t_httpUpdate_return ret = ESPhttpUpdate.update(client, url, currentVersion);

    if(ret == HTTP_UPDATE_FAILED){
        url.replace("ota.", "ota9.");
        client.setFingerprint(dtf_fingerprint); // Set the fingerprint for the fallback server

        #ifdef DTF_DEBUG
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        Serial.print(F("Trying fallback server: "));
        Serial.println(url);
        #endif

        ret = ESPhttpUpdate.update(client, url, currentVersion);
    }

    switch (ret) {
        case HTTP_UPDATE_FAILED:
            #ifdef DTF_DEBUG
            Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            #endif
            return DTF_UpdateResponse::UPDATE_FAILED;
            break;

        case HTTP_UPDATE_NO_UPDATES:
            #ifdef DTF_DEBUG
            Serial.println(F("No updates are available for this device."));
            #endif
            return DTF_UpdateResponse::NO_UPDATE_AVAILABLE;
            break;
        
        case HTTP_UPDATE_OK:
            #ifdef DTF_DEBUG
            Serial.println(F("Update succeeded."));
            #endif
            return DTF_UpdateResponse::UPDATE_SUCCEEDED;
            break;
        
        default:
            return DTF_UpdateResponse::NO_UPDATE_AVAILABLE;
    }
}