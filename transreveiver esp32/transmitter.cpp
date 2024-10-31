#include <esp_now.h>
#include <WiFi.h>

// MAC address of the receiver ESP32
uint8_t receiverAddress[] = {0xA8, 0x42, 0xE3, 0x5B, 0xC9, 0xC8};

// Pin where the toggle switch is connected
const int switchPin = 4;  // GPIO 4 for the toggle switch
bool ledState = false;    // LED state to be sent to the receiver

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    // Configure the switch pin as input with pull-up resistor
    pinMode(switchPin, INPUT_PULLUP);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the receiver peer
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
    // Read the state of the toggle switch
    bool switchState = digitalRead(switchPin) == LOW;  // LOW means the switch is "ON" position

    // If switchState is different from ledState, send the new state
    if (switchState != ledState) {
        ledState = switchState;  // Update the ledState to match the switch position
        esp_now_send(receiverAddress, (uint8_t *)&ledState, sizeof(ledState));
        Serial.printf("Sent LED state: %s\n", ledState ? "ON" : "OFF");
    }

    delay(100);  // Small delay to debounce the switch
}
