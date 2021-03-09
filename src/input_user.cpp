#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "move_base_msgs/MoveBaseActionGoal.h"
#include "final_assignment/target.h"
#include "std_srvs/SetBool.h"

//Global Variables

ros::Publisher pub;
ros::Subscriber sub;
move_base_msgs::MoveBaseActionGoal goal_pos;
float x_position;
float y_position;
final_assignment::target random_position;
std_srvs::SetBool wall_follower;


// Function for position
void positionCallback(const nav_msgs::Odometry::ConstPtr& msg) 
{
	x_position = msg->pose.pose.position.x;
	y_position = msg->pose.pose.position.y;
}



//Main Function

int main(int argc, char **argv)
{
  	ros::init(argc,argv,"user_interface");		
   	ros::NodeHandle n;		
	ros::Rate r(1);   //Creating 1 second delay

   	pub = n.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal",1000);  
   	sub = n.subscribe("/odom", 1000, positionCallback);

   	float mode;      
   	float x_desired;   //x value input from user
   	float y_desired;   //y value input from user
   	float x_val[]={-4,-4,-4, 5, 5,5};    //array of X coordinates
   	float y_val[]={-3, 2, 7,-7,-3,1};    //array of Y coordinates
	bool iscorrect = false;      


	ros::ServiceClient client1 = n.serviceClient<final_assignment::target>("random_coordinates");    //random coordinates service
	ros::ServiceClient client2 = n.serviceClient<std_srvs::SetBool>("/wall_follower_switch");        //wall follower service
   	
        while(mode!=-1)
 	{
                ROS_INFO("**************Final Assignment*********************");
		ROS_INFO("1. Robot moves randomly");
		ROS_INFO("2. Robot moves to the desired position");
		ROS_INFO("3. Robot starts to follow walls");
		ROS_INFO("4. Robot stops");
		ROS_INFO("To stop the program enter -1");
                ROS_INFO("Please enter your choice");
   		scanf("%f",&mode);
		
		ros::spinOnce();
		r.sleep();     //1 second delay
		
		if(mode==1){
	                        //Option 1 makes the robot move to a random coordinates. 
		
				client1.call(random_position);
				goal_pos.goal.target_pose.header.frame_id="map";
				goal_pos.goal.target_pose.pose.orientation.w=1;
				goal_pos.goal.target_pose.pose.position.x=random_position.response.x;
				goal_pos.goal.target_pose.pose.position.y=random_position.response.y;
				ROS_INFO("Random Coordintes: [%f,%f]",random_position.response.x,random_position.response.y);
				r.sleep();
				pub.publish(goal_pos);
				
				while((abs(random_position.response.x - x_position)>=0)||(abs(random_position.response.y - y_position)>=0))
				{
				ROS_INFO("Current position of Robot: [%f,%f]",x_position, y_position);					
				ros::spinOnce();
				r.sleep();
				}

				

		}
   		
   		
		if(mode==2){		//Option 2 asks to enter values of x and y from the user. Robot moves to those coordinates
				ROS_INFO("Available X coordinates (-4,-4,-4, 5, 5, 5)");
				ROS_INFO("Available Y coordinates (-3, 2, 7,-7,-3,1)");
				ROS_INFO("Enter the X coordinate");
				scanf("%f",&x_desired);
				ROS_INFO("Enter the Y coordinate");
				scanf("%f",&y_desired);

			        for (int i = 0; i <= 5; i++)   //to check if the values entered by the user match with the ones given
				{
				   if((x_desired==x_val[i])&&(y_desired==y_val[i])){
				   iscorrect = true;
					}
                                }

				if(iscorrect==true)    //if it is true then the robot goes to the coordinates
				{
				goal_pos.goal.target_pose.header.frame_id="map";
				goal_pos.goal.target_pose.pose.orientation.w=1;
				goal_pos.goal.target_pose.pose.position.x=x_desired;
				goal_pos.goal.target_pose.pose.position.y=y_desired;
				pub.publish(goal_pos);
				while((abs(x_desired-x_position)>=0)||(abs(y_desired-y_position)>=0))
				{
				ROS_INFO("Current position of Robot: [%f,%f]",x_position, y_position);					
				ros::spinOnce();
				r.sleep();
				}
				}

				else      //otherwise this error appears
				{	
				ROS_INFO("Incorrect coordinates entered, Please try again.");
				}
				iscorrect = false;
			    }
		
			if(mode==3){    //option 3,  Robot follows the walls
		
				ROS_INFO("Robot will start to follow the walls!");
				wall_follower.request.data=true;
				client2.call(wall_follower);  //wall follow service is called
			}
			
		
			if(mode==4){  //option 4,   robot stops
		
				wall_follower.request.data=false;
				client2.call(wall_follower);
				goal_pos.goal.target_pose.header.frame_id="map";
				goal_pos.goal.target_pose.pose.orientation.w=1;
				goal_pos.goal.target_pose.pose.position.x=x_position;
				goal_pos.goal.target_pose.pose.position.y=y_position;
				pub.publish(goal_pos);
				ROS_INFO("Robot has stopped");
 			}
          
		
    	}

	ros::spin();
    	return 0;
} 



