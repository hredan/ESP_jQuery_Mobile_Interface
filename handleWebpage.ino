/*
  handleWebpage.ino

  handleWebpage.ino is used by ESP_jQuery_Mobile_Interface.ino.

  Information and contribution at https://www.sleepuino.sourcecode3d.de/.

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

#include "handleWebpage.h"

#ifdef ESP32
WebServer* HandleWebpage::_webServer = nullptr;
#else
ESP8266WebServer* HandleWebpage::_webServer = nullptr;
#endif

HandleWebpage::HandleWebpage() {
#ifdef ESP32
  _webServer = new WebServer(80);
#else
  _webServer = new ESP8266WebServer(80);
#endif
}

void HandleWebpage::handleRoot() {  // When URI / is requested, send a web page
                                    // with a button to toggle the LED
  handleWebRequests();
}

void HandleWebpage::handleSetLed() {
  Serial.println("handleSetGain: " + _webServer->arg("plain"));

  if (_webServer->hasArg("led")) {
    String ledValue = _webServer->arg("led");
    Serial.printf("ledValue: %s\n", ledValue.c_str());
    if (ledValue == "true") {
#ifdef ESP32
      digitalWrite(LED_BUILTIN, HIGH);
#else
      digitalWrite(LED_BUILTIN, LOW);
#endif
    } else {
#ifdef ESP32
      digitalWrite(LED_BUILTIN, LOW);
#else
      digitalWrite(LED_BUILTIN, HIGH);
#endif
    }

    _webServer->send(200, "text/plane", "{\"success\": true}");
  } else {
    Serial.println("Error handleSetLed: missing argument led!");
    _webServer->send(200, "text/plane", "{\"success\": false}");
  }
}

void HandleWebpage::handleWebRequests() {
  if (!loadFromLittleFS(_webServer->uri())) {
    Serial.println("Error: handleWebRequests");
    String message = "File Not Detected\n\n";
    message += "URI: ";
    message += _webServer->uri();
    message += "\nMethod: ";
    message += (_webServer->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += _webServer->args();
    message += "\n";
    for (uint8_t i = 0; i < _webServer->args(); i++) {
      message += " NAME:" + _webServer->argName(i) +
                 "\n VALUE:" + _webServer->arg(i) + "\n";
    }
    _webServer->send(404, "text/plain", message);
    // Serial.println(message);
  }
}

bool HandleWebpage::loadFromLittleFS(String path) {
  bool returnValue = true;
  Serial.println("Load path: " + path);
  String dataType = "text/plain";

  if (path.endsWith("/")) path += "index.html";

  if (path.endsWith(".src"))
    path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html"))
    dataType = "text/html";
  else if (path.endsWith(".htm"))
    dataType = "text/html";
  else if (path.endsWith(".css"))
    dataType = "text/css";
  else if (path.endsWith(".js"))
    dataType = "application/javascript";
  else if (path.endsWith(".png"))
    dataType = "image/png";
  else if (path.endsWith(".gif"))
    dataType = "image/gif";
  else if (path.endsWith(".jpg"))
    dataType = "image/jpeg";
  else if (path.endsWith(".ico"))
    dataType = "image/x-icon";
  else if (path.endsWith(".xml"))
    dataType = "text/xml";
  else if (path.endsWith(".pdf"))
    dataType = "application/pdf";
  else if (path.endsWith(".zip"))
    dataType = "application/zip";
  if (LittleFS.exists(path)) {
    File dataFile = LittleFS.open(path.c_str(), "r");
    if (_webServer->hasArg("download")) dataType = "application/octet-stream";

    if (_webServer->streamFile(dataFile, dataType) != dataFile.size()) {
      // Serial.println("Error: streamed file has different size!");
      // returnValue = false;
    }
    dataFile.close();
  } else {
    Serial.println("Error: Path does not exist and will be redirect to root:");
    Serial.println(path);
    returnValue = loadFromLittleFS("/");
  }
  return returnValue;
}

void HandleWebpage::setupHandleWebpage() {
  // replay to all requests with same HTML
  _webServer->onNotFound(std::bind(&HandleWebpage::handleWebRequests, this));

  // replay to all requests with same HTML
  // Information about using std::bind ->
  // https://github.com/esp8266/Arduino/issues/1711

  _webServer->on("/", HTTP_GET, std::bind(&HandleWebpage::handleRoot, this));
  _webServer->on("/setLed", HTTP_POST,
                 std::bind(&HandleWebpage::handleSetLed, this));
  _webServer->begin();
}

void HandleWebpage::sendSuccess() {
  _webServer->send(200, "text/plane", "{\"success\": true}");
}

void HandleWebpage::handleClient() { _webServer->handleClient(); }
