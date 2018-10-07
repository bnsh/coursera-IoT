void setup() {
  pinMode(9, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting Servo demo.");
}

int lastpot = 0;
char buf[32];

void loop() {
  // put your main code here, to run repeatedly:
  int pot = analogRead(A0);
  if (!((-16 <= (pot-lastpot) && (pot-lastpot) <= 16))) {
    snprintf(buf, 32, "%d", pot);
    Serial.println(buf);
    lastpot = pot;
  }
  int val = map(pot, 0, 1024, 0, 255);
  analogWrite(9, val);
}
