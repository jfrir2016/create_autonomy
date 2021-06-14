/**
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2021, Nicolas Bortoni
 *
 */

#include "ca_behavior_tree/actions/get_location.h"

GetLoc::GetLoc(const std::string& name, const BT::NodeConfiguration& config)
    : BT::AsyncActionNode(name, config)
{
  Active = 0;
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe<std_msgs::String>("clients", 100,[this](const std_msgs::String::ConstPtr& msg)
    {
      //BT::StringView str = BT::StringView(msg->data.c_str());
      //Pose2D newPose = BT::convertFromString(str);
      //List[active] = newPose;
      //this->Active++;
      ROS_INFO("I heard: [%s]", msg->data.c_str());
    });
}

GetLoc::~GetLoc(){
};

BT::NodeStatus GetLoc::tick()
{

  //Set working poses
  struct Pose2D X1={-6.8,5.9,3.14};
  // struct Pose2D X2={-8.6,5.9,3.14};
  // struct Pose2D X3={-10.5,5.9,3.14};

  // Set the Pose table
  // Pose2D List[10];
  
  // Take the pose from the list
  Pose2D NextLocation = X1;
  static int i=0;
  if (this->Active != 0) {
    NextLocation = List[i];
    i++;
    i%=this->Active;
  }
  setOutput("NextLocation", NextLocation);

  ROS_INFO("Sending goal %f %f", NextLocation.x, NextLocation.y);

  ROS_INFO("Target reached");

  return BT::NodeStatus::SUCCESS;
}