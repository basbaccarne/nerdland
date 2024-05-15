// simple arcade button test with 3 buttons

// wiring:
// connect led ground with button ground on each button
// Button 1 : signal > D4 // LED > D5 (grove: D4)
// Button 2 : signal > D6 // LED > D7 (grove: D6)
// Button 3 : signal > A2 // LED > A3 (grove: A2)

// pins
const int button1 = 4;
const int button2 = 6;
byte button3 = A2;

const int led1 = 5;
const int led2 = 7;
byte led3 = A3;

// states
bool state1 = true;
bool state2 = true;
bool state3 = true;

void setup() {
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  if(!digitalRead(button1) & !state1){
    state1 = !state1;
    digitalWrite(led1, HIGH);
  }
  else if(digitalRead(button1) & state1){
    state1 = !state1;
    digitalWrite(led1, LOW);
  }
  // simple arcade button test with 3 buttons

// wiring:
// connect led ground with button ground on each button
// Button 1 : signal > D4 // LED > D5 (grove: D4)
// Button 2 : signal > D6 // LED > D7 (grove: D6)
// Button 3 : signal > A2 // LED > A3 (grove: A2)

// pins
const int button1 = 4;
const int button2 = 6;
byte button3 = A2;

const int led1 = 5;
const int led2 = 7;
byte led3 = A3;

// states
bool state1 = true;
bool state2 = true;
bool state3 = true;

void setup() {
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  if(!digitalRead(button1) & !state1){
    state1 = !state1;
    digitalWrite(led1, HIGH);
  }
  else if(digitalRead(button1) & state1){
    state1 = !state1;
    digitalWrite(led1, LOW);
  }
  
  if(!digitalRead(button2) & !state2){
    state2 = !state2;
    digitalWrite(led2, HIGH);
  }
  else if(digitalRead(button2) & state2){
    state2 = !state2;
    digitalWrite(led2, LOW);
  }

  if(!digitalRead(button3) & !state3){
    state3 = !state3;
    digitalWrite(led3, HIGH);
  }
  else if(digitalRead(button3) & state3){
    state3 = !state3;
    digitalWrite(led3, LOW);
  }
  
  delay(100);
}
