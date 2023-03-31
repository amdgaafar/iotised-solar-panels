void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("CAT\r");
  delay(1000);
}
