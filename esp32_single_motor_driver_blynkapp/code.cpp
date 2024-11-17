#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL31rIXwZeX"
#define BLYNK_TEMPLATE_NAME "4wd"
#define BLYNK_AUTH_TOKEN "1VYYKhd97F-x_SDUbJ-0O2grO9B2NWMJ"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "hplaptop";  // your wifi name
char pass[] = "laptophp";  // your wifi password

// Motor control pins
int M1PWM = 22;
int M2PWM = 19;
int M1F = 2;
int M1R = 4;
int M2F = 12;
int M2R = 13;

// Function to control Motor 1 direction
void setMotor1(bool forward) {
  if (forward) {
    digitalWrite(M1F, HIGH);
    digitalWrite(M1R, LOW);
    Serial.println("Motor 1 Forward at full speed");
  } else {
    digitalWrite(M1F, LOW);
    digitalWrite(M1R, HIGH);
    Serial.println("Motor 1 Reverse at full speed");
  }
}

// Function to control Motor 2 direction
void setMotor2(bool forward) {
  if (forward) {
    digitalWrite(M2F, HIGH);
    digitalWrite(M2R, LOW);
    Serial.println("Motor 2 Forward at full speed");
  } else {
    digitalWrite(M2F, LOW);
    digitalWrite(M2R, HIGH);
    Serial.println("Motor 2 Reverse at full speed");
  }
}

BLYNK_WRITE(V1)  // Motor 1 control
{
  int pinValue1 = param.asInt();
  bool forward = pinValue1 >= 0;
  setMotor1(forward);
  Serial.print("V1 Slider Value is ");
  Serial.println(pinValue1);
}

BLYNK_WRITE(V2)  // Motor 2 control
{
  int pinValue2 = param.asInt();
  bool forward = pinValue2 >= 0;
  setMotor2(forward);
  Serial.print("V2 Slider Value is ");
  Serial.println(pinValue2);
}

void setup() {
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(M1F, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M2R, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2PWM, OUTPUT);

  // Set PWM pins high to drive motors at full speed
  digitalWrite(M1PWM, HIGH);
  digitalWrite(M2PWM, HIGH);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
