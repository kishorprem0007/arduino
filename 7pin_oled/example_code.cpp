#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Pin definitions
#define OLED_DC     2  // Data/Command control
#define OLED_CS     5  // Chip Select
#define OLED_RESET  4  // Reset pin

// Create an SSD1306 SPI instance
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {  // Proper initialization
    Serial.println(F("SSD1306 initialization failed!"));
    for (;;);  // Halt execution
  }

  // Clear the display buffer
  display.clearDisplay();

  // Display "Hello, OLED!" message
  display.setTextSize(1);                   // Set text size
  display.setTextColor(SSD1306_WHITE);      // Set text color
  display.setCursor(0, 0);                  // Set cursor position
  display.println("Hello, OLED!");          // Print text to the buffer
  display.display();                        // Render the display buffer
}

void loop() {
  // Add any additional functionality here
}
