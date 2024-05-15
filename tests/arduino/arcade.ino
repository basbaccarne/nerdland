// simple arcade button test

// wiring:
// connect led ground with button ground
// connect button signal to digital 4
// connect led signal to digital 5
// (with a grove connector, this is port D4)

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  Serial.print("Button signal: ");
  Serial.println(digitalRead(4));
  if(!digitalRead(4)){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
  delay(100);
}
