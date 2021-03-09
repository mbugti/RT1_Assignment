#include "ros/ros.h"
#include "final_assignment/target.h"
#include <math.h>


// function for generating a random number between 2 numbers [M,N]
int randMToN(int M, int N) 
{ 
	return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
 }


// function for generating random coordinates out of the ones given: [(-4,-3);(-4,2);(-4,7);(5,-7);(5,-3);(5,1)]


bool randTarget(final_assignment::target::Request &req, final_assignment::target::Response &res)
{

	int index_pos;	
	float x_val[] = {-4,-4,-4, 5, 5, 5};  //array for x coordinates
	float y_val[] = {-3, 2, 7, -7, -3, 1};  //array for y coordinates
	index_pos = randMToN(0,5);
	res.x = x_val[index_pos];   
	res.y = y_val[index_pos];	
        ROS_INFO("Random target coordinates: [%f] [%f]", res.x, res.y); 
        return true;

}

//Main Function
int main(int argc, char **argv)
{
   // Initialize the node, setup the NodeHandle for handling the communication with the ROS
   // system
   ros::init(argc, argv, "random_server");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/random_coordinates", randTarget);
   ros::spin();

   return 0;
}
