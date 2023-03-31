#include <ESP8266WiFi.h>
#include <SPI.h>

char *ssid = "a wifi";
char *password = "zxcZXC00";

char server[] = "https://apiv2.favoriot.com";
const String APIKEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Ikdyb3VwMiIsInJlYWRfd3JpdGUiOnRydWUsImlhdCI6MTYzNjc3NDg2M30.vRDFdkCV4n6V5kJ6VJVe8ErX_cEZw8EDB6ckfm6yCjY";
const String DEVICE = "esp@Group2";

String message;
bool messageReady;

WiFiClient client;

void setup()
{
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  sendStream();
  delay(100);
}

// Send stream to FAVORIOT
void sendStream()
{
  // Monitor Serial communication
  while (Serial.available())
  {
    message = Serial.readString();
    messageReady = true;
  }
  if (messageReady)
  {
    // Serial.println(message);
    messageReady = false;

    String txt = "ON HIGH"; // Text to send

    // If there's a successful connection
    if (client.connect(server, 80))
    {
      Serial.println(F("connected"));
      Serial.println("");
      // Build the data field
      String json = "{\"device_developer_id\":\"esp@Group2\",\"data\":{\"Light Intensity\":\"" + message + "\"}}";
      int thisLength = json.length();

      Serial.println("STATUS : Sending data..."); // Display sending status
      client.println("POST /v2/streams HTTP/1.1");
      client.println("Host: apiv2.favoriot.com");
      client.print(String("apikey: "));
      client.println(APIKEY);
      client.println("Content-Type: application/json");
      client.println("cache-control: no-cache");
      client.print("Content-Length: ");
      client.println(thisLength);
      client.println("Connection: close");

      client.println();
      client.println(json);

      Serial.println(json);                  // display sent data
      Serial.println("STATUS : Data sent!"); // display sent status
    }
    else
    {
      // If you didn't get a connection to the server:
      Serial.println(F("connection failed"));
    }
  }
}