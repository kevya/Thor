# Thor
<p align="center">
<img src="https://github.com/kevya/Thor/blob/master/Thor.png" width="194" height="260">
</p>

Software for the [Open Source 3D printed robotic arm with six degrees of freedom by AngelLM](https://github.com/AngelLM/Thor)

This repository contains two custom methods for controlling Thor (each method has its own Arduino .ino file):
* Basic GUI created using controlP5 in Processing
* MoveIt! Motion Planning using ROS Kinetic

Created as an alternative for the developer’s Asgard.gui found [here](https://github.com/AngelLM/asgard) which uses G-Code to operate the arm. In an attempt to incorporate ROS compatibility, the GUI and Arduino scripts were written to use Serial communication.

Refer to [this doc](https://docs.google.com/document/d/1FVpkL5BBwQ95qeYnpAs9fkwruu6XzP2zu2IkwuMoEOY/edit) for my build documentation and electronics details.
