#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseStamped.h"
#include "math.h"
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>


double x1=0.0,x2=0.0,x3=0.0;
double yp1=0.0,yp2=0.0,yp3=0.0;
double z1=0.0,z2=0.0,z3=0.0;
double diff12x=0.0,diff12y=0.0,diff12z=0.0,diff13x=0.0,diff13y=0.0,diff13z=0.0;
double offset=3.0;




mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}
mavros_msgs::State current_state2;
void state_cb2(const mavros_msgs::State::ConstPtr& msg){
    current_state2 = *msg;
}
mavros_msgs::State current_state3;
void state_cb3(const mavros_msgs::State::ConstPtr& msg){
    current_state3 = *msg;
}

void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  /*ROS_INFO("Seq1: [%d]", msg->header.seq);
  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);*/
  x1=msg->pose.pose.position.x;
  yp1=msg->pose.pose.position.y;
  z1=msg->pose.pose.position.z;
}
void chatterCallback2(const nav_msgs::Odometry::ConstPtr& msg)
{
 /* ROS_INFO("Seq2: [%d]", msg->header.seq);
  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z); */
  x2=msg->pose.pose.position.x;
  yp2=msg->pose.pose.position.y;
  z2=msg->pose.pose.position.z;
}
void chatterCallback3(const nav_msgs::Odometry::ConstPtr& msg)
{
  /*ROS_INFO("Seq3: [%d]", msg->header.seq);
  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);*/
  x3=msg->pose.pose.position.x;
  yp3=msg->pose.pose.position.y;
  z3=msg->pose.pose.position.z;
}

void compute()
{
  diff12x=x2-x1;
  diff12y=yp2-yp1;
  diff12z=z2-z1;
  diff13x=x3-x1;
  diff13y=yp3-yp1;
  diff13z=z3-z1;
  /*cc=sqrt(pow(diff12x,2)+pow(diff12y,2)); */
  x2=offset*cos(M_PI/3)+x1;
  yp2=offset*sin(M_PI/3)+yp1;
  z2=z1;
  x3=offset*cos(M_PI/3)+x2;
  yp3=offset*sin(M_PI/3)+yp2;
  z3=z1;
  /*ros::Publisher local_pos_pub = n.advertise<geometry_msgs::PoseStamped> ("/uav1/mavros/setpoint_position/local", 10);
  ros::Rate loop_rate(10.0);
  
  
  geometry_msgs::PoseStamped pose;
  pose.pose.position.x = 0;
  pose.pose.position.y = 0;
  pose.pose.position.z = 3;
}*/
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "swarmtest");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle nh;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  
  /*compute();*/
  /*ros::Publisher cpub = n.advertise<geometry_msgs::PoseStamped>("/uav1/mavros/setpoint_position/local", 1000);
  /*mavros_msgs/GlobalPositionTarget*/
  /*ros::Rate loop_rate(10);
  
  geometry_msgs::PoseStamped msg;
  msg.pose.position.x = 0;
  msg.pose.position.y = 0;
  msg.pose.position.z = 2;

  cpub.publish(msg);*/

  /**std::stringstream ss;
  /*ss << "hello world " << count;*/
  /*msg.data = ss.str(); */
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("/uav1/mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("/uav1/mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/uav1/mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/uav1/mavros/set_mode");
    /*further control of uavs*/
    ros::Subscriber state_sub2 = nh.subscribe<mavros_msgs::State>("/uav2/mavros/state", 10, state_cb2);
    ros::Publisher local_pos_pub2 = nh.advertise<geometry_msgs::PoseStamped>("/uav2/mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client2 = nh.serviceClient<mavros_msgs::CommandBool>("/uav2/mavros/cmd/arming");
    ros::ServiceClient set_mode_client2 = nh.serviceClient<mavros_msgs::SetMode>("/uav2/mavros/set_mode");
    
    ros::Subscriber state_sub3 = nh.subscribe<mavros_msgs::State>("/uav3/mavros/state", 10, state_cb3);
    ros::Publisher local_pos_pub3 = nh.advertise<geometry_msgs::PoseStamped>("/uav3/mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client3 = nh.serviceClient<mavros_msgs::CommandBool>("/uav3/mavros/cmd/arming");
    ros::ServiceClient set_mode_client3 = nh.serviceClient<mavros_msgs::SetMode>("/uav3/mavros/set_mode");

    ros::Subscriber sub = nh.subscribe("/uav1/mavros/global_position/local", 1000, chatterCallback);
    ros::Subscriber sub2 = nh.subscribe("/uav2/mavros/global_position/local", 1000, chatterCallback2);
    ros::Subscriber sub3 = nh.subscribe("/uav3/mavros/global_position/local", 1000, chatterCallback3);


    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected && !current_state2.connected && !current_state3.connected){
        ros::spinOnce();
        rate.sleep();
    }

    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 2;
    
    compute();

    geometry_msgs::PoseStamped pose2;
    pose2.pose.position.x = x2;
    pose2.pose.position.y = yp2;
    pose2.pose.position.z = 2;
    ROS_INFO("Y coordinate UAV2->: [%f]", yp2);
    ROS_INFO("z coordinate UAV2->: [%f]", z2);

    geometry_msgs::PoseStamped pose3;
    pose3.pose.position.x = x3;
    pose3.pose.position.y = yp3;
    pose3.pose.position.z = 2;


    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub2.publish(pose2);
        ros::spinOnce();
        rate.sleep();
    }
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub3.publish(pose3);
        ros::spinOnce();
        rate.sleep();
    }


    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;
    

    mavros_msgs::SetMode offb_set_mode2;
    offb_set_mode2.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd2;
    arm_cmd2.request.value = true;
  
    
    mavros_msgs::SetMode offb_set_mode3;
    offb_set_mode3.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd3;
    arm_cmd3.request.value = true;

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){
        if( current_state.mode != "OFFBOARD" && current_state2.mode != "OFFBOARD" && current_state3.mode != "OFFBOARD" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))){
            if( set_mode_client.call(offb_set_mode) && set_mode_client2.call(offb_set_mode2) && set_mode_client3.call(offb_set_mode3) && 
                offb_set_mode.response.mode_sent && offb_set_mode2.response.mode_sent && offb_set_mode3.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        } else {
            if( !current_state.armed && !current_state2.armed && !current_state3.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) && arming_client2.call(arm_cmd2) && arming_client3.call(arm_cmd3) &&
                    arm_cmd.response.success && arm_cmd2.response.success && arm_cmd3.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }

        local_pos_pub.publish(pose);
        local_pos_pub2.publish(pose2);
        local_pos_pub3.publish(pose3);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}








