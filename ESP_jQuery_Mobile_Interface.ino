/*
  ESP_jQuery_Mobile_Interface.ino

  ESP_jQuery_Mobile_Interface.ino is an example how to switch on a board LED via web interface for ESP8266 and ESP32. 

  Information and contribution at https://github.com/hredan/ESP_jQuery_Mobile_Interface.

  Copyright (C) 2021  André Herrmann (hredan)
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifdef ESP32
  #include <WiFi.h>  // https://github.com/espressif/arduino-esp32
#else
  #include <ESP8266WiFi.h>  // https://github.com/esp8266/Arduino
#endif

#include "LittleFS.h"
#include "handleWebpage.h"

// declaration of needed instances
HandleWebpage *handleWebpage;

void setup() {
  Serial.begin(115200);
  Serial.print("\n");

  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH);  // set led off

  // init little filesystem
  if (LittleFS.begin()) {
    Serial.print("LittleFS started successfully\n");
#ifdef ESP32
    Serial.printf("FS total Bytes %d\n", LittleFS.totalBytes());
    Serial.printf("FS used Bytes %d\n", LittleFS.usedBytes());
#else
    FSInfo fs_info;
    LittleFS.info(fs_info);
    Serial.printf("FS total Bytes %d\n", fs_info.totalBytes);
    Serial.printf("FS used Bytes %d\n", fs_info.usedBytes);
#endif
  } else {
    Serial.print("Error: Could not start LittleFS!\n");
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("SleepUinoPreDev");

  handleWebpage = new HandleWebpage();
  handleWebpage->setupHandleWebpage();

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);
}

void loop() {
  dnsServer.processNextRequest();
  handleWebpage->handleClient();
}
