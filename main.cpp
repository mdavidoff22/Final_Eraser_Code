#include <Arduino.h>
#include <Servo.h>
//import arduino and servo libraries

Servo servoLeft;
Servo servoRight;
//declare the right and left servos

void setup()
{ pinMode(7, INPUT);
  pinMode(5, INPUT);
  pinMode(10, INPUT);
  //assign right and left wisker inputs to pins 7 and 5
  //include input of IR sensor connected to pin 10

  servoLeft.attach(13);
  servoRight.attach(12);
  //attach the servos to their respective pins
}

//1 is up direction value, any other int value (0 is used) is down
//a function to move the servo motors in right directions and speeds to move the eraser up the board evenly and at a fine rate.
//a parameter of the number of seconds the servos run and the direction it moves vertically
void move(int time, int direct)
{ 
  if (direct == 1) {
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1700);
    delay(time);
  }
  else {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
  }
}

//A function to detach the servos such that they don't have any signals going to them, such that they no longer run
void detach()
{ servoLeft.detach();
  servoRight.detach();
}

//a loop to run the code and call the above functions based on conditionals 
void loop() { 
  byte wLeft = digitalRead(5);
  byte wRight = digitalRead(7);
  //copy left pin signal status (set to 1 or 0 depending if the wisker is touching the pin or not) to wLeft and do the same for the right
  int irLeft = digitalRead(10);
  //do the same for the signal status of the IR sensor

  //conditionals that check if either/both/none of the headers gain a signal, meaning a wisker is touched
  //if a wisker is detected as touched, then stop the motors from running by calling the detach function
  //otherwise, the loop keeps running and calling the up function, spinning the servos constantly in intervals of 20 milliseconds
  if(irLeft == 1) {
    if((wLeft == 0) || (wRight == 0)) {
      move(5000, 0); 
      detach();
    }
    else
    { move(20, 1); 
    }
  }
}
//OVERALL: The code, when activated by a detection of an IR signal, brings the eraser up from its resting place at the bottom of the whiteboard by using servos to roll up string. Once the eraser gets to the top of the board, it physically nudges a whisker to hit one of the two headers. When this happens, the servos move in the opposite directions, lowering the eraser back down to its resting position and disconnecting the servos.
//the goal of this program is to move an eraser from the bottom of a whiteboard up to the top of it, where it should be detected and stoped from moving any higher, completing its erase.
