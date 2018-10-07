void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void blink(int time) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}

void loop() {
  for (int i = 0; i < 5; ++i) blink(500);
  for (int i = 0; i < 5; ++i) blink(2000);
}
