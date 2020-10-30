//For use with Rosserial and MoveIt!

#include <Stepper.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/JointState.h>

#define stepsPerRevolution 200

//Setup Node
ros::NodeHandle  nh;
Stepper Base(stepsPerRevolution, 28, 36);
Stepper Art2Step_a(stepsPerRevolution, 26, 34);
Stepper Art2Step_b(stepsPerRevolution, 24, 32);
Stepper Art3Step(stepsPerRevolution, 22, 30);
Stepper Art4Step(stepsPerRevolution, 23, 31);
Stepper Art5Step_a(stepsPerRevolution, 25, 33);
Stepper Art5Step_b(stepsPerRevolution, 27, 35);

//Angles
double base_temp;
double base_angle = 0;
double art2_angle=0;
double art3_angle=0;
double art4_angle=0;
double art5_angle=0;
double art6_angle=0;

int n = 0;

//Stepper function, move based on published joint states
void stepper_cb(const sensor_msgs::JointState& cmd_msg) {
    base_temp = radiansToDegrees(cmd_msg.position[0]);
    delay(500);
    base_angle = radiansToDegrees(cmd_msg.position[0]);

    //Move arm only if the joint state has stopped updating
    if(base_temp != 0 && base_temp == base_angle && n == 0)
    {
     //Convert joint state radians to degrees
     base_angle = radiansToDegrees(cmd_msg.position[0]);
     art2_angle = radiansToDegrees(cmd_msg.position[1]);
     art3_angle = radiansToDegrees(cmd_msg.position[2]);
     art4_angle = radiansToDegrees(cmd_msg.position[3]);
     art5_angle = radiansToDegrees(cmd_msg.position[4]);
     art6_angle = 0; //radiansToDegrees(cmd_msg.position[5]);
    
      //Start a loop to move all joints at the same time to desired state
      //This will have to be modified to allow the arm to update to a new state without restarting Moveit
      
      int art1=0, art2=0, art3=0, art4 = 0, art5 = 0, art6=0;
      while (1)
      {
  
        //Use art# as step count
        //Compare it to the absolute value of the determined max step count
        //Step, then increment

        //1.8 is 360/200, the degrees for one step
        //The constant multiples in each art was found by roating the joint a known degree
          //and measuring the offset, which in this case is the gear ratio
          
       if(art1 < fabs((base_angle/1.8)*20))
        {
          if(base_angle < 0)
              Base.step(-1);
          else
              Base.step(1);
          art1++;
        }

        if(art2 < fabs((art2_angle/1.8)*120))
        {
          if (art2_angle < 0)
            {
             Art2Step_a.step(-1);
             Art2Step_b.step(-1);
            }
         else
            {
            Art2Step_a.step(1);
            Art2Step_b.step(1);
            }
           art2++;
        }

        if(art3 < fabs((art3_angle/1.8)*120))
        {
           if(art3_angle < 0)
              Art3Step.step(-1);
           else
              Art3Step.step(1);
           art3++;
        }

        if(art4 < fabs((art4_angle/1.8)*10))
        {

           if(art4_angle < 0)
              Art4Step.step(-1);
           else
              Art4Step.step(1);
           art4++;
        }

        if(art5 < fabs((art5_angle/1.8))*8)
        {
           if(art5_angle < 0)
           {
             Art5Step_a.step(1);
             Art5Step_b.step(-1);
           }
           else
           {
             Art5Step_a.step(-1);
             Art5Step_b.step(1);
           }  
           art5++;        

        }
        
        if(art6 < fabs((art6_angle/1.8))*16)
        {
           if(art5_angle < 0)
           {
             Art5Step_a.step(1);
             Art5Step_b.step(1);
           }
           else
           {
             Art5Step_a.step(-1);
             Art5Step_b.step(-1);
           }  
           art6++;        

        }   
    }
  }
}

//Subscribe to the joint states
ros::Subscriber<sensor_msgs::JointState> sub("joint_states", stepper_cb);

void setup() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);

  //Setup stepper speeds
  delay(1);
  Base.setSpeed(50);
  Art2Step_a.setSpeed(100);
  Art2Step_b.setSpeed(100);
  Art3Step.setSpeed(100);
  Art4Step.setSpeed(50);
  Art5Step_a.setSpeed(50);
  Art5Step_b.setSpeed(50);


}

void loop() {
    nh.spinOnce();
}


double radiansToDegrees(double position_radians)
{
  return position_radians * 57.2958;
}

//Used to move Art2

/*void art2Move(float deg)
{

  
  if(deg < 0)
  {
    for(int s=0; s<=abs(deg*16); s++)
        {
           Art2Step_a.step(-1);
           Art2Step_b.step(-1);
        }
  }

  if(deg > 0)
  {
    for(int s=0; s<=abs(deg*16); s++)
        {
           Art2Step_a.step(1);
           Art2Step_b.step(1);
        }
    
  }
  */
}
