/*
  Intelligent Light-Tracking System
  Authors: Ganga2807,Poornima020,npavan0206
  Description:
    Engineered an intelligent light-tracking system using LDR sensors and microcontrollers
    to dynamically align with the brightest light source. Implemented real-time motor control
    for precise tracking, boosting energy efficiency in smart lighting and optical systems.
*/

#include <Servo.h>

// Create servo objects
Servo servoHoriz;  // Horizontal servo (pan)
Servo servoVert;   // Vertical servo (tilt)

// Starting positions (mid-range)
int angleHoriz = 90; // Horizontal starting angle
int angleVert  = 90; // Vertical starting angle

// Define servo limits
const int horizServoMin = 10;
const int horizServoMax = 180;
const int vertServoMin  = 10;
const int vertServoMax  = 180;

// Define LDR sensor pins (using analog inputs)
const int ldrTopRight    = A1; // Top right LDR
const int ldrTopLeft     = A2; // Top left LDR
const int ldrBottomRight = A0; // Bottom right LDR
const int ldrBottomLeft  = A3; // Bottom left LDR

void setup() {
  // Attach servos to Arduino pins
  servoHoriz.attach(10);  // Horizontal servo on pin 10
  servoVert.attach(9);    // Vertical servo on pin 9
  
  // Initialize servos to the starting position
  servoHoriz.write(angleHoriz);
  servoVert.write(angleVert);
  
  // Small delay for stabilization
  delay(500);
}

void loop() {
  // Read LDR values
  int topLeft     = analogRead(ldrTopLeft);
  int topRight    = analogRead(ldrTopRight);
  int bottomLeft  = analogRead(ldrBottomLeft);
  int bottomRight = analogRead(ldrBottomRight);
  
  // Calculate average values for top, bottom, left, and right
  int avgTop    = (topLeft + topRight) / 2;
  int avgBottom = (bottomLeft + bottomRight) / 2;
  int avgLeft   = (topLeft + bottomLeft) / 2;
  int avgRight  = (topRight + bottomRight) / 2;
  
  // --- Vertical Adjustment ---
  // If the top receives less light than the bottom, tilt upward.
  if (avgTop < avgBottom) {
    angleVert = max(angleVert - 1, vertServoMin);
  }
  // If the bottom receives less light than the top, tilt downward.
  else if (avgBottom < avgTop) {
    angleVert = min(angleVert + 1, vertServoMax);
  }
  // Write the updated vertical angle to the servo.
  servoVert.write(angleVert);
  
  // --- Horizontal Adjustment ---
  // If the left side receives more light than the right, pan left.
  if (avgLeft > avgRight) {
    angleHoriz = max(angleHoriz - 1, horizServoMin);
  }
  // If the right side receives more light than the left, pan right.
  else if (avgRight > avgLeft) {
    angleHoriz = min(angleHoriz + 1, horizServoMax);
  }
  // Write the updated horizontal angle to the servo.
  servoHoriz.write(angleHoriz);
  
  // Delay for smooth movement
  delay(50);
}