// libraries
// https://github.com/Seeed-Studio/Grove_Gesture
// https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip

#include <Wire.h>
#include "paj7620.h"
#include "Ultrasonic.h"

// Gesture detection settings (I2C)
#define GES_REACTION_TIME 300
#define GES_ENTRY_TIME 800
#define GES_QUIT_TIME 500

// Timers
unsigned long currentMillis = millis();
unsigned long previousDelay = 0;
unsigned long previousMillis_gesReaction = 0;
unsigned long previousMillis_gesEntryTime = 0;
unsigned long previousMillis_gesQuitReaction = 0;

// ThumbStick Values (A0)
int sensorValue1;
int sensorValue2;

// Set up distance sensor (D2)
Ultrasonic ultrasonic(2);
long RangeInCentimeters;

// Identify buttons
const int button1 = 5;
const int button2 = 7;
byte button3 = A3;
byte button4 = A2;

// Output parameters
int thumb_x = 0;
int thumb_y = 0;
int gest_x = 0;
int gest_y = 0;
int dist = 0;

// Default settings (for reset)
int init_thumb_x = 0;
int init_thumb_y = 0;
int init_gest_x = 0;
int init_gest_y = 0;
int init_dist = 0;

void setup()
{
  // Open serial communications
  Serial.begin(9600);

  // Set baseline values
  resetValues();

  // Initialize gesture control
  uint8_t error = 0;
  error = paj7620Init(); // initialize Paj7620 registers
  if (error)
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }

  // Sett-up buttons
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

}

void resetValues()
{
  thumb_x = init_thumb_x;
  thumb_y = init_thumb_y;
  gest_x = init_gest_x;
  gest_y = init_gest_y;
  dist = init_dist;
}

void getThumb()
{
  // Read the sensor
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);

  // Count the values up or down
  if (sensorValue1 < 500-50)
  {
    thumb_x++;
  }
  if (sensorValue1 > 500+50)
  {
    thumb_x--;
  }
  if (sensorValue2 < 500-50)
  {
    thumb_y++;
  }
  if (sensorValue2 > 500+50)
  {
    thumb_y--;
  }

  // Debugging prints
  // Serial.println("");
  // Serial.print("Thumb 1: ");
  // Serial.print(sensorValue1);
  // Serial.print(" Thumb 2: ");
  // Serial.println(sensorValue2);
}

void getDist()
{
  // Measure
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  // Map
  if (RangeInCentimeters < 100)
  {
    dist = map(RangeInCentimeters, 0, 100, 0, 20);
  }
  // debugging prints
  // Serial.print(RangeInCentimeters);//0~400cm
  // Serial.println(" cm");
}

void getGesture()
{
  // error prevention
  uint8_t data = 0, data1 = 0, error;
  // read the data
  error = paj7620ReadReg(0x43, 1, &data); // Read Bank_0_Reg_0x43/0x44 for gesture result.
  // interpret the data
  if (!error)
  {
    switch (data) // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      if (currentMillis - previousMillis_gesEntryTime > GES_REACTION_TIME)
      {
      case GES_RIGHT_FLAG:
        // Serial.println("Up");
        gest_x++;
        break;
      case GES_LEFT_FLAG:
        // Serial.println("Down");
        gest_x--;
        break;
      case GES_UP_FLAG:
        // Serial.println("Left");
        if (gest_y > 0)
        {
          gest_y--;
        }
        break;
      case GES_DOWN_FLAG:
        // Serial.println("Right");
        if (gest_y < 2)
        {
          gest_y++;
        }
        break;
        previousMillis_gesEntryTime = currentMillis;
      }
    }
  }
}

void loop()
{
  // Timer
  currentMillis = millis();

  // Get the data and print the result to firefly each 200 ms
  if (currentMillis - previousDelay > 200)
  {
    if (!digitalRead(button1))
    {
      getThumb();
    }
    if (!digitalRead(button2))
    {
      getGesture();
    }
    if (!digitalRead(button3))
    {
      getDist();
    }
    if (!digitalRead(button4))
    {
      resetValues();
    }

    Serial.print(thumb_x);
    Serial.print("|");
    Serial.print(thumb_y);
    Serial.print("|");
    Serial.print(gest_x);
    Serial.print("|");
    Serial.print(gest_y);
    Serial.print("|");
    Serial.println(dist);
    previousDelay = currentMillis;
  }
}
