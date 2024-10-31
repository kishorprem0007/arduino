#include <esp_now.h>
#include <WiFi.h>

// Pin where the LED is connected
const int ledPin = 2;  // GPIO 2 for LED

bool ledState = false;  // Initial LED state

// Updated callback function for receiving data with esp_now_recv_info parameter
void onDataRecv(const esp_now_recv_info *recvInfo, const uint8_t *incomingData, int len) {
    memcpy(&ledState, incomingData, sizeof(ledState));
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.printf("Received LED state: %s\n", ledState ? "ON" : "OFF");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // Configure LED pin as output
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);  // Initial state OFF

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register callback function for receiving data
    esp_now_register_recv_cb(onDataRecv);  // Corrected function signature
    Serial.println("Receiver ready");
}

void loop() {
    // Nothing needed in loop as data is handled by the onDataRecv callback
}
