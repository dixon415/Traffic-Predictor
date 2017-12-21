int ledOuter = 12;
int ledOuter1 = 8;
int ledInner = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledOuter, OUTPUT);
  pinMode(ledOuter1, OUTPUT);
  pinMode(ledInner, OUTPUT);
  pinMode(A1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledOuter, HIGH);
  digitalWrite(ledInner, HIGH);
  digitalWrite(ledOuter1, LOW);
  delay(10);
  analogWrite(A1, 255);
  delay(10);
  digitalWrite(ledOuter, LOW);
  digitalWrite(ledInner, LOW);
  digitalWrite(ledOuter1, HIGH);
  delay(10);
  analogWrite(A1, 100);
  delay(10);
}
