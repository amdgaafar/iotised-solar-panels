#include <Servo.h>
#include <ArduinoJson.h>

#define VOLT A4

String message = "";
bool messageReady = false;

// Pin numbers of LDRs (analog inputs)
const int ldr_top = 0;
const int ldr_bot = 1;

// Pin numbers of Motors (PWM inputs)
const int servo_vertical_pin = 9;

// Servo objects
Servo servo_vertical;
int servov_pos = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ldr_top, OUTPUT);
  pinMode(ldr_bot, OUTPUT);

  if (!ina219.begin())
  {
    Serial.println("Failed to find INA219 chip");
    while (1)
    {
      Serial.print(".");
      delay(100);
    }
  }
}

void loop()
{
  // Monitor Serial communication
  while (Serial.available())
  {
    message = Serial.readString();
    messageReady = true;
  }
  // Only process message if there's one
  if (messageReady)
  {
    // The only messages we'll parse will be formatted in JSON
    DynamicJsonDocument doc(1024); // ArduinoJson version 6+
    // Attempt to deserialize the message
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }
    if (doc["type"] == "request")
    {
      doc["type"] = "response";
      // Get data from analog sensors
      doc["TOP"] = analogRead(ldr_top);
      doc["BOT"] = analogRead(ldr_bot);
      serializeJson(doc, Serial);
    }
    messageReady = false;
  }
}
