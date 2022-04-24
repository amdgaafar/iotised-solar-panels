#include <Servo.h>
#include <ArduinoJson.h>

#define VOLT A4

String message = "";
bool messageReady = false;

// Pin numbers of LDRs (analog inputs)
const int ldr_top = A0;
const int ldr_bot = 1;

// Pin numbers of Motors (PWM inputs)
const int servo_vertical_pin = 9;

// Servo objects
Servo servo_vertical;
int servov_pos = 0;

int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ldr_top, INPUT);
  pinMode(ldr_bot, INPUT);
  pinMode(2, INPUT);
}

void loop()
{
  int ldr_top_val = analogRead(ldr_top);
  buttonState = digitalRead(2);
  bool state = true;
  while (buttonState == HIGH)
  {
    if (state)
    {
      Serial.print(String(ldr_top_val));
      state = false;
    }
    buttonState = digitalRead(2);
  }
  delay(500);
}
