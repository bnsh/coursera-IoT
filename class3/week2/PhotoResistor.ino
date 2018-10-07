int led_state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); // Start things in the off state.
  Serial.println("If A0 drops below 256 we turn the LED on.");
}

void loop() {
  char buf[64];

  int photoresistor = analogRead(A0);
  if ((photoresistor < 256) && (led_state == LOW)) {
      Serial.println("Man it got dark out.");
      led_state = HIGH;
  }
  if ((photoresistor >= 256) && (led_state == HIGH)) {
    Serial.println("Morning sunshine!");
    led_state = LOW;
  }
  digitalWrite(8, led_state);
}
