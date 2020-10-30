# Control Thor with MoveIt!

Developed using rosserial on ROS Kinetic on Ubuntu 16.04.

A proper workspace and rosserial installation  are required. See the [ROS wiki](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup) for instructions on setting up rossserial.

Instructions:
* Install and setup rosserial, see the [ROS wiki](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup) for details
* Build the packages 'moveit-config-Thor' and 'thor_arm_description-master' in your workspace.
* Upload Thor_ROS.ino to the Arduino.
* Open MoveIt!: `roslaunch moveit-config-Thor demo.launch`
  * To view the published joint_states: `rostopic echo /joint_states`
* Setup the port `sudo chmod -R 777 /dev/ttyACM1` -Replace `/dev/ttyACM1` with desired port
  * Run rosserial_python: `rosrun rosserial_python serial_node.py _port:=/dev/ttyACM1 _baud:=115200
`
* Done, move the arm in MoveIt!, plan/execute, and watch the arm move!

Note: Due to using stepper motors instead of servos, the motors do not have predetermined degree points. Therefore, the arm can only be moved once using the motion planning framework. To move the arm again, restart MoveIt. This will eventually be fixed...

Resources: https://www.instructables.com/id/ROS-MoveIt-Robotic-Arm-Part-2-Robot-Controller/
