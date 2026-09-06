#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);
const int LED_PIN = 2; // LED tích hợp trên ESP32

void handleRoot() {
    String html = "<html><body>";
    html += "<h1>CubeSat LED Control</h1>";
    html += "<p><a href=\"/on\"><button style=\"padding:10px 20px; font-size:20px;\">Turn ON</button></a></p>";
    html += "<p><a href=\"/off\"><button style=\"padding:10px 20px; font-size:20px;\">Turn OFF</button></a></p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleLedOn() {
    digitalWrite(LED_PIN, HIGH);
    server.send(200, "text/html", "<h2>LED is ON</h2><p><a href=\"/\">Back</a></p>");
}

void handleLedOff() {
    digitalWrite(LED_PIN, LOW);
    server.send(200, "text/html", "<h2>LED is OFF</h2><p><a href=\"/\">Back</a></p>");
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/on", handleLedOn);
    server.on("/off", handleLedOff);

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}