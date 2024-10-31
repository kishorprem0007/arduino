#include <esp_now.h>
#include <WiFi.h>

// MAC address of the receiver ESP32
uint8_t receiverAddress[] = {0xA8, 0x42, 0xE3, 0x5B, 0xC9, 0xC8};  // Updated MAC address

bool ledState = false;  // Initial LED state

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("Transmitter ready");
}

void loop() {
    // Toggle LED state
    ledState = !ledState;

    // Send LED state to the receiver
    esp_now_send(receiverAddress, (uint8_t *)&ledState, sizeof(ledState));
    Serial.printf("Sent LED state: %s\n", ledState ? "ON" : "OFF");

    delay(2000);  // Send every 2 seconds
}
