

#include <ESP8266WiFi.h>    //https://github.com/esp8266/Arduino
#include "handleWebpage.h"
#include "LittleFS.h"

//declaration of needed instances
HandleWebpage *handleWebpage;
   
void setup()
{
    Serial.begin(115200);
    Serial.print("\n");

    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    digitalWrite(LED_BUILTIN, HIGH);  // set led off
    
    //init little filesystem
    if (LittleFS.begin())
    {
        Serial.print("LittleFS started successfully\n");
        FSInfo fs_info;
        LittleFS.info(fs_info);
        Serial.printf("FS total Bytes %d\n", fs_info.totalBytes);
        Serial.printf("FS used Bytes %d\n", fs_info.usedBytes);
    }
    else
    {
        Serial.print("Error: Could not start LittleFS!\n");
    }

    handleWebpage = new HandleWebpage();
    handleWebpage->setupHandleWebpage();

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("SleepUinoPreDev");

    // if DNSServer is started with "*" for domain name, it will reply with
    // provided IP to all DNS request
    dnsServer.start(DNS_PORT, "*", apIP);
}

void loop()
{   
    dnsServer.processNextRequest();
    handleWebpage->handleClient();
}
