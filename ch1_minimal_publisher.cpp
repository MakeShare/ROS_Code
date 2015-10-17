#include <ros/ros.h>
#include <std_msgs/Float64.h>
int main(int argc, char **argv) {
	ros::init(argc, argv, "minimal_publisher1"); // 节点（node）名是 "minimal_publisher1"
	ros::NodeHandle n; // 创建与ROS通信的发布者对象
	ros::Publisher my_publisher_object = n.advertise<std_msgs::Float64>("topic1", 1);
	//"topic1" 是我们要发布的话题名
	// 数字变量"1" 代表缓冲区的大小为1，需要网络备份可以将数值调大
	
	std_msgs::Float64 input_float; //创建一个类型为 "Float64"的变量,
	// 该类型的定义参见: /opt/ros/indigo/share/std_msgs
	// 所有在ROS话题下发布的信息都必须有一个预定义的格式（如数据类型），
	// 这样订阅者才知道如何解读数据流
	
	input_float.data = 0.0;
	
	// 此处无限循环 (仅针对本示例), 检测到ROS错误时终止
	while (ros::ok())
	{
		// 本循环没有休眠设定, 将充分使用CPU时间
		// 杀鸡用牛刀时非常浪费的行为！
		input_float.data = input_float.data + 0.001; //每次迭代加0.001
		my_publisher_object.publish(input_float); // 向话题发布数据类型为 Float64 的信息"topic1"
	}
}
