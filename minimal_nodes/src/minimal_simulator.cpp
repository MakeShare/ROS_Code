// minimal_simulator node: 
// wsn example node that both subscribes and publishes 
// does trivial system simulation, F=ma, to update velocity given F specified on topic "force_cmd" 
// publishes velocity on topic "velocity" 
#include<ros/ros.h> 
#include<std_msgs/Float64.h> 
std_msgs::Float64 g_real_pos;
std_msgs::Float64 g_vel;

void myCallback(const std_msgs::Float64& message_holder) {
    ROS_INFO("received force value is: %f", message_holder.data);
    g_vel.data = message_holder.data; // post the received data in a global var for access by 
    // main prog. 
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "minimal_simulator"); //name this node  
    ros::NodeHandle nh; // node handle 
    ros::Subscriber my_subscriber_object = nh.subscribe("vel_cmd", 1, myCallback);

    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("real_pos", 1);
    double mass = 1.0;
    double dt = 0.01; //10ms integration time step 
    double sample_rate = 1.0 / dt; // compute the corresponding update frequency 
    ros::Rate naptime(sample_rate);
    g_real_pos.data = 0.0; //initialize velocity to zero 
    g_vel.data = 0.0; // initialize force to 0; will get updated by callback 
    while (ros::ok()) {
        g_real_pos.data = g_real_pos.data + g_vel.data * dt; 
        my_publisher_object.publish(g_real_pos); // publish the system state (trivial--1-D) 
        ROS_INFO("real position = %f", g_real_pos.data);
        ros::spinOnce(); 
        naptime.sleep(); 

    }
    return 0; // should never get here, unless roscore dies 
} 
