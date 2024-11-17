#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL32DXJM2K5"
#define BLYNK_TEMPLATE_NAME "4wd dual driver"
#define BLYNK_AUTH_TOKEN "nHGDsQqPtmEEJN5VYixbAT_MUEJGqzt1"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "hplaptop";  // your WiFi name
char pass[] = "laptophp";  // your WiFi password

// Motor control pins
int M1PWM = 22;  // Left front motor speed
int M2PWM = 19;  // Right front motor speed
int M3PWM = 21;  // Left rear motor speed
int M4PWM = 18;  // Right rear motor speed

int M1F = 2;     // Left front motor forward
int M1R = 4;     // Left front motor reverse
int M2F = 12;    // Right front motor forward
int M2R = 13;    // Right front motor reverse
int M3F = 27;    // Left rear motor forward
int M3R = 26;    // Left rear motor reverse
int M4F = 33;    // Right rear motor forward
int M4R = 25;    // Right rear motor reverse

// Light control pins
int frontLightPin = 14;   // GPIO for front light
int backLightPin = 15;    // GPIO for back light

// Motor control functions
void moveForward() {
  digitalWrite(M1F, HIGH);
  digitalWrite(M1R, LOW);
  digitalWrite(M2F, HIGH);
  digitalWrite(M2R, LOW);
  digitalWrite(M3F, HIGH);
  digitalWrite(M3R, LOW);
  digitalWrite(M4F, HIGH);
  digitalWrite(M4R, LOW);
  Serial.println("Moving Forward");
}

void moveBackward() {
  digitalWrite(M1F, LOW);
  digitalWrite(M1R, HIGH);
  digitalWrite(M2F, LOW);
  digitalWrite(M2R, HIGH);
  digitalWrite(M3F, LOW);
  digitalWrite(M3R, HIGH);
  digitalWrite(M4F, LOW);
  digitalWrite(M4R, HIGH);
  Serial.println("Moving Backward");
}

void turnLeft() {
  digitalWrite(M1F, LOW);
  digitalWrite(M1R, HIGH);
  digitalWrite(M2F, HIGH);
  digitalWrite(M2R, LOW);
  digitalWrite(M3F, LOW);
  digitalWrite(M3R, HIGH);
  digitalWrite(M4F, HIGH);
  digitalWrite(M4R, LOW);
  Serial.println("Turning Left");
}

void turnRight() {
  digitalWrite(M1F, HIGH);
  digitalWrite(M1R, LOW);
  digitalWrite(M2F, LOW);
  digitalWrite(M2R, HIGH);
  digitalWrite(M3F, HIGH);
  digitalWrite(M3R, LOW);
  digitalWrite(M4F, LOW);
  digitalWrite(M4R, HIGH);
  Serial.println("Turning Right");
}

void stopMotors() {
  digitalWrite(M1F, LOW);
  digitalWrite(M1R, LOW);
  digitalWrite(M2F, LOW);
  digitalWrite(M2R, LOW);
  digitalWrite(M3F, LOW);
  digitalWrite(M3R, LOW);
  digitalWrite(M4F, LOW);
  digitalWrite(M4R, LOW);
  Serial.println("Motors Stopped");
}

// Blynk virtual pin handlers for button presses
BLYNK_WRITE(V1) {  // Forward Button
  int value = param.asInt();
  if (value) {
    moveForward();
  } else {
    stopMotors();
  }
}

BLYNK_WRITE(V2) {  // Backward Button
  int value = param.asInt();
  if (value) {
    moveBackward();
  } else {
    stopMotors();
  }
}

BLYNK_WRITE(V3) {  // Left Button
  int value = param.asInt();
  if (value) {
    turnLeft();
  } else {
    stopMotors();
  }
}

BLYNK_WRITE(V4) {  // Right Button
  int value = param.asInt();
  if (value) {
    turnRight();
  } else {
    stopMotors();
  }
}

// Light control handlers
BLYNK_WRITE(V5) {  // Front Light Button
  int lightState = param.asInt();
  digitalWrite(frontLightPin, lightState);  // Turn front light on or off
  Serial.println(lightState ? "Front Light ON" : "Front Light OFF");
}

BLYNK_WRITE(V6) {  // Back Light Button
  int lightState = param.asInt();
  digitalWrite(backLightPin, lightState);  // Turn back light on or off
  Serial.println(lightState ? "Back Light ON" : "Back Light OFF");
}

void setup() {
  Serial.begin(9600);

  // Motor pin setup
  pinMode(M1F, OUTPUT); pinMode(M1R, OUTPUT);
  pinMode(M2F, OUTPUT); pinMode(M2R, OUTPUT);
  pinMode(M3F, OUTPUT); pinMode(M3R, OUTPUT);
  pinMode(M4F, OUTPUT); pinMode(M4R, OUTPUT);
  pinMode(M1PWM, OUTPUT); digitalWrite(M1PWM, HIGH);
  pinMode(M2PWM, OUTPUT); digitalWrite(M2PWM, HIGH);
  pinMode(M3PWM, OUTPUT); digitalWrite(M3PWM, HIGH);
  pinMode(M4PWM, OUTPUT); digitalWrite(M4PWM, HIGH);

  // Light pin setup
  pinMode(frontLightPin, OUTPUT);
  pinMode(backLightPin, OUTPUT);
  digitalWrite(frontLightPin, LOW);  // Initialize front light as OFF
  digitalWrite(backLightPin, LOW);   // Initialize back light as OFF

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
