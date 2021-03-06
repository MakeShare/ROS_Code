// minimal_controller node: 
// wsn example node that both subscribes and publishes--counterpart to minimal_simulator 
// subscribes to "velocity" and publishes "force_cmd" 
// subscribes to "vel_cmd" 
#include<ros/ros.h> 
#include<std_msgs/Float64.h> 
#include<cmath>
//global variables for callback functions to populate for use in main program 
std_msgs::Float64 g_pos_cmd;
std_msgs::Float64 g_vel; // this one does not need to be global... 



void myCallbackPosCmd(const std_msgs::Float64& message_holder) {

    ROS_INFO("received postion command value is: %f", message_holder.data);
    g_pos_cmd.data = message_holder.data;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "minimal_controller"); //name this node 
    // when this compiled code is run, ROS will recognize it as a node called "minimal_controller" 
    ros::NodeHandle nh; // node handle 

    ros::Subscriber my_subscriber_object2 = nh.subscribe("pos_cmd", 1, myCallbackPosCmd);

    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("vel_cmd", 1);

    double a = 1.0; // velocity feedback gain 
    double dt_controller = 0.1; //specify 10Hz controller sample rate (pretty slow, but 
    //illustrative) 
    double sample_rate = 1.0 / dt_controller; // compute the corresponding update frequency 
    ros::Rate naptime(sample_rate); // use to regulate loop rate 

    g_vel.data = 0.0; // initialize force to 0; will get updated by callback 
    g_pos_cmd.data = 0.0; // init velocity command to zero 
    double vel_max = 0.0;
	
    double d = 0.0;
    int p = 0;

    while (ros::ok()) {
        d = g_pos_cmd.data - 0;
	vel_max = sqrt(d*a);
if(d>0){
        if(p == 0 && g_vel.data <= vel_max){g_vel.data = g_vel.data + a*dt_controller;}
        else if (p == 0 && g_vel.data >= vel_max){p = 1;}
        else if (p == 1 && g_vel.data >= 0){g_vel.data = g_vel.data - a*dt_controller;}
        else if (p == 1 && g_vel.data <= 0){p = 2;}
        else if (p == 2){g_vel.data = 0;}
}

        my_publisher_object.publish(g_vel); // publish the control effort computed by this 
        //controller 
        ROS_INFO("velocity command = %f, %i, %f", g_vel.data, p, vel_max);
        ros::spinOnce(); //allow data update from callback; 
        naptime.sleep(); // wait for remainder of specified period; 
    }
    return 0; // should never get here, unless roscore dies 
} 
