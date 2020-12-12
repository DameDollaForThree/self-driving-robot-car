#include <Servo.h>
#include "Demon-Slayer.h"

void setup()
{
  Serial.begin(9600);
  drive.setup();
  Servo.setup();
  distanceSensor.setup();
  Servo_2.setup();
  display.setup();
  button.setup();
  bump.setup();
  
}

const int STOPPED = 0;
const int DRIVE_FORWARD = 1;
const int SPIN = 2;
const int ROTATE = 3;
const int DRIVE_AC = 4;

int state = DRIVE_FORWARD;
long int start_time;

void loop()
{
  Serial.println(state);
  Serial.println(button.isPressed()); 
  Serial.println(distanceSensor.get_distance());
switch(state){
//  case BUMP:
//    state = DRIVE_AC;
//    break;

  case DRIVE_AC:
    if (distanceSensor.get_distance() <= 10){
        state = ROTATE;
        drive.stop();
        start_time = millis();
    } else if (millis() > start_time + 2000) {
        state = DRIVE_FORWARD;
        start_time = millis();
    }
    break;
    
  case DRIVE_FORWARD:
    if (bump.isPressed()) {
      state = DRIVE_AC;
    } else if (distanceSensor.get_distance() <= 10){
        state = ROTATE;
        drive.stop();
        start_time = millis();
    }
    break;
    
   case ROTATE: 
    if (bump.isPressed()) {
      state = DRIVE_AC;
    } else if (millis() > start_time + 1000) {
        start_time = millis();
        state = SPIN;
      }
    break;


   case SPIN: 
    if (bump.isPressed()) {
      state = DRIVE_AC;
    } else if (millis() > start_time + 1000) {
        state = DRIVE_FORWARD;
        start_time = millis();
      }
    break;

  }

  switch (state) {

    case DRIVE_AC:
      drive.backward(220);
      break;
      
    case DRIVE_FORWARD:
      drive.backward(150);
      break;
      
    case ROTATE:
      Servo.rotate(180);
      Servo_2.rotate(180);
      delay(1000);
      Servo.rotate(0);
      Servo_2.rotate(0);
      delay(1000);
      break;

    case SPIN:
      drive.spinLeft(120);
      break;
  }
}


    
//  drive.spinLeft();
//  delay(1000);
//  drive.spinRight();
//  delay(1000);
//        Serial.println("Testing distanceSensor...");
//  
//  
//  	 for (int c = 0; c < 5000; c++) {
//  	 char str[50];
//  	 sprintf(str, "distanceSensor: distance= %d", distanceSensor.get_distance());
//  	 Serial.println(str);
//  	 delay(1);
//  	}
//        Serial.println("Testing display...");
//  
//  	display.clear();
//  	display.drawCircle(3,3, 3);
//        Serial.println("Testing button...");
//  
//  
//  	for (int c = 0; c < 500; c++) {
//  	     char str[50];
//  	     sprintf(str, "button: pressed = %s", button.isPressed() ? "yes" : "no");
//  	     Serial.println(str);
//  	     delay(1);
//  	}
//        Serial.println("Testing bump...");
//  
//  
//  	for (int c = 0; c < 500; c++) {
//  	     char str[50];
//  	     sprintf(str, "bump: pressed = %s", bump.isPressed() ? "yes" : "no");
//  	     Serial.println(str);
//  	     delay(1);
//  	}
        

