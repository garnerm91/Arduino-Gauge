#include <Stepper.h>

int stepsPerRevolution = 600;        // Change this to suit the number of steps per revolution for your motor
int stepperSpeed = 50;
int pos; // pos is 0-100
int val; // val is exact step skipping last and first 50
int idiot = 60;
Stepper x27(stepsPerRevolution, 2, 3, 4, 5); // initialize the stepper library


void x27zero()
{
  x27.setSpeed(stepperSpeed);                 // Set the speed to 130. Simply won't move cw on 5V. Works fine with 12V on L293 pin 8
  x27.step(-stepsPerRevolution);
  delay(10);
  x27.step(50);
  pos = 0;
  val = 0;  
}


void x27move(unsigned int npos)
{
 if (pos != npos){
   val = npos * 5 - pos *5;
   pos = npos;
   x27.step(val);
 }
}

void updateled()//turns on/off led
{
 if (pos >= idiot){
    digitalWrite(6, HIGH);
 }
 else{
    digitalWrite(6, LOW);
 }
}

void looper() {
  loopUp();
  loopDown();
}

void loopUp() {
  for (int i = 0; i <= 99; i++) {
  x27move(i);
  updateled();
 }

}

void loopDown() {
  for (int i = 99; i >= 0; i--) 
   {  
   x27move(i);
  updateled();
  }
}
void setup() 
{
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  x27zero();
  delay(1000);
} 


void loop() 
{
  looper();
  }
