//This file contains all necessary code to operate the Thor arm with the commands given from the Processing GUI
//Note: Make sure that the GUI is not running when trying to upload this file to Arduino

#include <Stepper.h>
#include <Servo.h>

//Art 1
#define dirPin1 36     
#define stepPin1 28

//Art 2a
#define dirPin12 34     
#define stepPin12 26

//Art 2b
#define dirPin2 32     
#define stepPin2 24

//Art 3
#define dirPin3 30     
#define stepPin3 22

//Art 4
#define dirPin4 31     
#define stepPin4 23

//Art 5/6 a
#define dirPin6 33     
#define stepPin6 25

//Art 5/6 b
#define dirPin7 35     
#define stepPin7 27

//Gripper
#define grip 41

#define stepsPerRevolution 200

//Opto Sensors
#define optoPin1 42
#define optoPin2 44
#define optoPin3 46
#define optoPin4 48
#define optoPin5 49
#define optoPin6 47


//Init Stepper/Servo motors
Stepper art1Step(stepsPerRevolution, stepPin1, dirPin1);
Stepper art2Step(stepsPerRevolution, stepPin2, dirPin2);
Stepper art22Step(stepsPerRevolution, stepPin12, dirPin12);
Stepper art3Step(stepsPerRevolution, stepPin3, dirPin3);
Stepper art4Step(stepsPerRevolution, stepPin4, dirPin4);
Stepper art6Step(stepsPerRevolution, stepPin6, dirPin6);
Stepper art7Step(stepsPerRevolution, stepPin7, dirPin7);

Servo gripper;


void setup() {
  Serial.begin(9600);
  gripper.attach(grip);
}

void loop() { 
  //Get data from the GUI in Processing
  if(Serial.available()>= 3){
    char state = Serial.read();
    int stepSpeed = Serial.read();

    //Convert rotation string into an integer
    String rot = Serial.readString();
    double deg = ((rot[1] - '0')*100 + (rot[3]- '0')*10
              + (rot[5] - '0'))/18.0;

  switch(state) {
    //Art 1 right
    case 'r':
        art1Step.setSpeed(stepSpeed);
        art1Step.step(deg*stepsPerRevolution);
        delay(500);
        break;

    //Art 1 left
    case 'l':
        art1Step.setSpeed(stepSpeed);
        art1Step.step(-deg*stepsPerRevolution);
        delay(500);
        break;

  //Art 2 right
  case 'j':
        art22Step.setSpeed(stepSpeed);
        art2Step.setSpeed(stepSpeed);
        delay(500);
        break;
        
   //There are two steppers in Art 2, so mimic simultaneous movement by stepping each one once at a time 
        for(int s=0; s<=(deg*stepsPerRevolution*4); s++)
          {
            art22Step.step(1);
            art2Step.step(1);
          }
        delay(500);
        break;

  //Art 2 left
  case 'k':
         art22Step.setSpeed(stepSpeed);
         art2Step.setSpeed(stepSpeed);
      
         for(int s=0; s<=(deg*stepsPerRevolution*4); s++)
          {
             art22Step.step(-1);
             art2Step.step(-1);
          }
            delay(500);
            break;

  //Art 3 left
  case 'n':
        art3Step.setSpeed(stepSpeed);
        art3Step.step(-deg*stepsPerRevolution);
        delay(500);
        break;

  //Art 3 Right
   case 'm':
        art3Step.setSpeed(stepSpeed);
        art3Step.step(deg*stepsPerRevolution);
        delay(500);
        break;
 
  //Art 4 Right
   case 'h':
        art4Step.setSpeed(stepSpeed);
        art4Step.step(deg*stepsPerRevolution/2);
        delay(500);
        break;
  
  //Art 4 Left
   case 'i':
        art4Step.setSpeed(stepSpeed);
        art4Step.step(-deg*stepsPerRevolution/2);
        delay(500);
        break;


//Art 5 and 6 use the same motors, just in differnt directions
    //Art 5: alternate signs
    //Art 6: same signs

  //Art 5 Right
   case 'o':
      art6Step.setSpeed(stepSpeed);
      art7Step.setSpeed(stepSpeed);

      for(int s=0; s<=(deg*stepsPerRevolution/2); s++)
      {
        art6Step.step(-1);    
        art7Step.step(1);
      } 
        delay(500);
        break;

  //Art 5 Left
   case 'p':
      art6Step.setSpeed(stepSpeed);
      art7Step.setSpeed(stepSpeed);

      for(int s=0; s<=(deg*stepsPerRevolution/2); s++)
      {
        art6Step.step(1);    
        art7Step.step(-1);
      } 
        delay(500);
        break;

  //Art 6
   case 'q':
      art6Step.setSpeed(stepSpeed);
      art7Step.setSpeed(stepSpeed);

      for(int s=0; s<=(deg*stepsPerRevolution/2); s++)
      {
        art6Step.step(-1);    
        art7Step.step(-1);
      } 
        delay(500);
        break;

  //Art 6
    case 't':
      art6Step.setSpeed(stepSpeed);
      art7Step.setSpeed(stepSpeed);

      for(int s=0; s<=(deg*stepsPerRevolution/2); s++)
      {
        art6Step.step(1);    
        art7Step.step(1);
      } 
        delay(500);
        break;

  //DEMO, moves the arm around
   case 'd':
        stepSpeed = 200;
        deg = 2;
        art1Step.setSpeed(stepSpeed);
        art1Step.step(-deg*stepsPerRevolution);
                delay(250);

        art1Step.setSpeed(stepSpeed);
        art1Step.step(deg*stepsPerRevolution);
        
                delay(250);
         art22Step.setSpeed(stepSpeed);
        art2Step.setSpeed(stepSpeed);

       for(int s=0; s<=(3000); s++)
          {
            art22Step.step(-1);
            art2Step.step(-1);
          }
                delay(250);

        art3Step.setSpeed(400);
        art3Step.step(-3000);

        delay(250);

        art4Step.setSpeed(200);
        art4Step.step(-300);
    
        delay(250);

        art4Step.setSpeed(200);
        art4Step.step(300);
        
        delay(250);
        
        art4Step.setSpeed(200);
        art4Step.step(300);
        
        delay(250);

        art4Step.setSpeed(200);
        art4Step.step(-500);
        
        delay(250);

         for(int s=0; s<6900; s++)
      {
         art22Step.setSpeed(500);
         art22Step.step(1);
      
         art2Step.setSpeed(500);
         art2Step.step(1);
      }
        delay(250);

        art3Step.setSpeed(400);
        art3Step.step(3000);

        delay(250);

        for(int s=0; s<3500; s++)
      {
         art22Step.setSpeed(500);
         art22Step.step(-1);
      
         art2Step.setSpeed(500);
         art2Step.step(-1);
      }
        delay(250);

        break;


    //Stop, needs to be a hardware stop    
    case 's':
        break;

    //calibrate (HOME)    
    case 'c':
        calibrate();
        break;

  //Gripper Open
    case 'z':
    gripper.write(0);    
    delay(1000);        
    break;
    
  //Gripper Close
    case 'x':      
    gripper.write(110);    
    delay(250); 
    break;
    
       }

     }
}

//Uses Optosensors to set the arm in the Home position
void calibrate()
{
    int opto1 = digitalRead(optoPin1);
    int opto2 = digitalRead(optoPin2);
    int opto3 = digitalRead(optoPin3);
    int opto4 = digitalRead(optoPin5);
   // int opto5 = digitalRead(optoPin5);
    //int opto6 = digitalRead(optoPin6);
  

    art2Step.setSpeed(200);
    art22Step.setSpeed(200);
    while (opto2 == HIGH)
    {
        Serial.println(opto2);
        opto2 = digitalRead(optoPin2);       
        art2Step.step(-1);
        art22Step.step(-1);
    }

    art3Step.setSpeed(200);
    
    while (opto3 == LOW)
    {   
        Serial.println(opto3);
        opto3 = digitalRead(optoPin3);       
        art3Step.step(-1);
    }
        Serial.println(opto3); 



      art1Step.setSpeed(100);

    //TODO Art 4-6
}    
