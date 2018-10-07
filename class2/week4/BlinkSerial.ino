void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Send 1 to turn the LED on, and send 0 to turn it off. Any other characters are *ignored*");
}

void loop() {
  // put your main code here, to run repeatedly:
  int ch = Serial.read();

  if (ch == '1') {
    Serial.println("Turned LED on.");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (ch == '0') {
    Serial.println("Turned LED off.");
    digitalWrite(LED_BUILTIN, LOW);
  }
}
