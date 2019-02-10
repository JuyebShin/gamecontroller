/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/gamecontroller/qnode.hpp"
#include "../include/gamecontroller/robocupController_msg.h"
#include "../include/gamecontroller/robocupController2.h"


namespace gamecontroller {

ros::Publisher controller_pub;

QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)
{}

QNode::~QNode()
{
    if(ros::isStarted())
    {
        ros::shutdown();
        ros::waitForShutdown();
    }
    wait();
}

bool QNode::init() {
    ros::init(init_argc,init_argv,"gamecontroller");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    controller_pub = n.advertise<gamecontroller::robocupController2>("gamecontroller",100);
    start();

    return true;
}

void QNode::run() {

    ros::Rate loop_rate(100);

    while ( ros::ok() )
    {
        //        ready();

        ros::spinOnce();

        loop_rate.sleep();
    }
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::ready()
{
    gamecontroller::robocupController_msg RCmsg;
    RCmsg.state = 1;
    RCmsg.penalty = 1;

    controller_pub.publish(RCmsg);

}


}  // namespace robocup_controller

