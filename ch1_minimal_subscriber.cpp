#include<ros/ros.h>
#include<std_msgs/Float64.h>
void myCallback(const std_msgs::Float64& message_holder)
{
	// 真正有效的操作都在本回调函数中完成
	// 每当有新的信息发布在“topic1”下时，它就会启动
	// 由于这个函数是伴随消息事件启动的，所以它轮番检测是否有新信息的过程并不占用CPU时间
	// ROS_INFO()函数与printf()函数的功能类似，区别在于它向默认的rosout话题发布信息，
	// 从而避免了因显示命令所导致的频率减缓，发布了信息同样可以用于查看和记录之用。
	ROS_INFO("received value is: %f",message_holder.data);
	// 利用接收到的数据，我们真的可以在这儿玩儿出花儿来。。。结果我们只是把它显示出来而已。。。
}
int main(int argc, char **argv)
{
	ros::init(argc,argv,"minimal_subscriber"); //为节点命名
	// 当运行编译后的节点程序时，ROS会通过它的节点名"minimal_subscriber"来进行识别
	ros::NodeHandle n; // 与新节点建立通讯关联
	// 创建一个订阅者对象并订阅“topic1”话题
	// “myCallback”回调函数在有新信息发布到topic1时启动
	// 真正的回调工作都是在函数内完成的
	ros::Subscriber my_subscriber_object= n.subscribe("topic1",1,myCallback);
	ros::spin(); //这里与“while(1)”所实现的功能类似，区别在于新信息到达时会强制刷新
	return 0; // 除非roscore宕机，你应该用于用不到这行
}
