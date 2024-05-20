// simple arcade button test with 4 buttons

// pins
const int button1 = 5;
const int button2 = 7;
byte button3 = A3;
byte button4 = A2;

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
}

void loop()
{
  Serial.print("button 1: ");
  Serial.print(digitalRead(button1));
  Serial.print("  //  button 2: ");
  Serial.print(digitalRead(button2));
  Serial.print("  //  button 3: ");
  Serial.print(digitalRead(button3));
  Serial.print("  //  Reset button: ");
  Serial.println(digitalRead(button4));
  delay(200);
}
