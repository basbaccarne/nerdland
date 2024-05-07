// libraries
// https://github.com/Seeed-Studio/Grove_Gesture
// https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger/archive/master.zip

#include <Wire.h>
#include "paj7620.h"
#include "Ultrasonic.h"

// Gesture detection settings (I2C)
#define GES_REACTION_TIME 300  // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME 800     // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s).
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

// Output parameters
int thumb_x = 0;
int thumb_y = 0;
int gest_x = 0;
int gest_y = 0;
int dist = 0;

void setup() {
  Serial.begin(9600);

  // initialize gesture control
  uint8_t error = 0;
  error = paj7620Init();  // initialize Paj7620 registers
  if (error) {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  } else {
    Serial.println("INIT OK");
  }
}

void getThumb() {
  // Read the sensor
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);

  // Count the values up or down
  if (sensorValue1 < 200) {
    thumb_x--;
  }
  if (sensorValue1 > 500) {
    thumb_x++;
  }
  if (sensorValue2 < 200) {
    thumb_y++;
  }
  if (sensorValue2 > 500) {
    thumb_y--;
  }

  // Debugging prints
  // Serial.println("");
  // Serial.print("Thumb 1: ");
  // Serial.print(sensorValue1);
  // Serial.print(" Thumb 2: ");
  // Serial.println(sensorValue2);
}

void getDist() {
  // Measure
  RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  // Map
  if(RangeInCentimeters < 100){
    dist = map(RangeInCentimeters, 0, 100, 0, 20);
  }
  // debugging prints
  // Serial.print(RangeInCentimeters);//0~400cm
  //Serial.println(" cm");
}

void getGesture() {
  // error prevention
  uint8_t data = 0, data1 = 0, error;
  // read the data
  error = paj7620ReadReg(0x43, 1, &data);  // Read Bank_0_Reg_0x43/0x44 for gesture result.
  // interpret the data
  if (!error) {
    switch (data)  // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      if (currentMillis - previousMillis_gesEntryTime > GES_REACTION_TIME) {
        case GES_RIGHT_FLAG:
          // Serial.println("Right");
          gest_x++;
          break;
        case GES_LEFT_FLAG:
          // Serial.println("Left");
          gest_x--;
          break;
        case GES_UP_FLAG:
          // Serial.println("Up");
          gest_y++;
          break;
        case GES_DOWN_FLAG:
          // Serial.println("Down");
          gest_y--;
          break;
        previousMillis_gesEntryTime = currentMillis;
        }
    }
  }
}

  void loop() {
    // Timer
    currentMillis = millis();

    // Get the thumb data  and print the result to firefly each 200 ms
    if (currentMillis - previousDelay > 200) {
      getThumb();
      getGesture();
      getDist();

      Serial.print(thumb_x);
      Serial.print("//");
      Serial.print(thumb_y);
      Serial.print("//");
      Serial.print(gest_x);
      Serial.print("//");
      Serial.print(gest_y);
      Serial.print("//");
      Serial.println(dist);
      previousDelay = currentMillis;
    }


    
  }
