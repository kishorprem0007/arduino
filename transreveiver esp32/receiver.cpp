#include <esp_now.h>
#include <WiFi.h>

const int ledPin = 2;  // GPIO pin connected to the LED

bool ledState = false;  // Initial LED state

// Updated callback function to match the new esp_now_recv_cb_t signature
void onDataReceive(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
    memcpy(&ledState, incomingData, sizeof(ledState));

    // Update LED state based on received data
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.printf("LED state received: %s\n", ledState ? "ON" : "OFF");
}

void setup() {
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT);  // Set LED pin as output

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register callback function for incoming data with the updated function signature
    esp_now_register_recv_cb(onDataReceive);

    Serial.println("Receiver ready");
}

void loop() {
    delay(1000);  // Wait to allow time for receiving data
}
