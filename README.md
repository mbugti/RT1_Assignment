# Malook Bugti RT1 Final Assignment
## Overview of the Overall Projecct

**Robot response to user input:** 
1. Random movent in the enviroment.
2. Ask the user for coordinates as input.
3. Follows the external walls.
4. Reaches and stop at the last and required last position.

## Computational Graph



## Contents of the Package
- **random_node.cpp:** Generating random coordinates out of the 6 coordinates, [(-4,-3);(-4,2);(-4,7);(5,-7);(5,-3);(5,1)]
- **input_user.cpp:** Node for interaction with user
- **destination.srv:** Service file for x and y coordinates
- **wall_following.py:** Service for following walls
- **gmapping.launch:** For launching the simulator 
- **move.launch:** For launching move_base
- **input_user.launch:** For launching the main user interface

## Steps for running the code
Direct to your ROS workspace and type
```
catkin_make
```
Use the following command for launching the simulator:
```
roslaunch final_assignment gmapping.launch
```
Type the following command to move:
```
roslaunch final_assignment move.launch
```
Finally, type the following command to take input from user:
```
roslaunch final_assignment input_user.launch
```
## Room for further improvments and Limitations of the Package
Upon taking input from user the robot move towards the target location. For example, the user will be unable to provide new coordinates unless and untill it has reached its target position. In between movement to the target position the user should be able to stop the robot and insert set of coordinates. When Option #3 is selected, during its movement the robot continues to follow its path besides the external walls and it cannot be stopped. A delicate feedback system should be implaced that continuously checks to inform the user weather a specific key is being pressed or not. 

## Requirements
- Ubuntu (Linux) or Docker Image https://hub.docker.com/r/carms84/rpr
- (Robot Operating System) http://wiki.ros.org/
