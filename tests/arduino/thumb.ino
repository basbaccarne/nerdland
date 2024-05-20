// Thumbstick test
// https://wiki.seeedstudio.com/Grove-Thumb_Joystick/

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int sensorValue1 = analogRead(A0);
    int sensorValue2 = analogRead(A1);

    Serial.print("X:");
    Serial.print(sensorValue1, DEC);
    Serial.print(" // Y:");
    Serial.println(sensorValue2, DEC);
    delay(100);
}