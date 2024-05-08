// libraries
#include <Wire.h>
#include "paj7620.h"

// Gesture detection settings
#define GES_REACTION_TIME 300  // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME 800     // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s).
#define GES_QUIT_TIME 500

// Timers
unsigned long currentMillis = millis();
unsigned long previousMillis_gesReaction = 0;
unsigned long previousMillis_gesEntryTime = 0;
unsigned long previousMillis_gesQuitReaction = 0;


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

void getGesture() {
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);  // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error) {
    switch (data)  // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        if (currentMillis - previousMillis_gesEntryTime > GES_REACTION_TIME) {
          paj7620ReadReg(0x43, 1, &data);
          if (data == GES_FORWARD_FLAG) {
            Serial.println("Forward");
            delay(GES_QUIT_TIME);
          } else if (data == GES_BACKWARD_FLAG) {
            Serial.println("Backward");
            delay(GES_QUIT_TIME);
          } else {
            Serial.println("Right");
          }
          break;
          case GES_LEFT_FLAG:
            delay(GES_ENTRY_TIME);
            paj7620ReadReg(0x43, 1, &data);
            if (data == GES_FORWARD_FLAG) {
              Serial.println("Forward");
              delay(GES_QUIT_TIME);
            } else if (data == GES_BACKWARD_FLAG) {
              Serial.println("Backward");
              delay(GES_QUIT_TIME);
            } else {
              Serial.println("Left");
            }
            break;
            previousMillis_gesEntryTime = currentMillis;
        }
        // delay(GES_ENTRY_TIME);

      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        } else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        } else {
          Serial.println("Up");
        }
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if (data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        } else if (data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        } else {
          Serial.println("Down");
        }
        break;
    }
  }
  delay(100);
}

void loop() {
  // General clock
  currentMillis = millis();
  // Get Gesture
  getGesture();
}
