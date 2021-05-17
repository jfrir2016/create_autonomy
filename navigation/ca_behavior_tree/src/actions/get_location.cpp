/**
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2021, Nicolas Bortoni
 *
 */

#include "ca_behavior_tree/actions/get_location.h"


BT::NodeStatus GetLoc::tick()
{
  //Set working poses
  struct Pose2D X1={-6.8,5.9,3.14};
  struct Pose2D X2={-8.6,5.9,3.14};
  struct Pose2D X3={-10.5,5.9,3.14};

  //Set the Pose table
  Pose2D List[3];
  List[0]=X1;
  List[1]=X2;
  List[2]=X3;
  
  // Take the pose from the list
  Pose2D NextLocation;
  static int i=0;
  NextLocation = List[i];
  i++;
  i%=3;

  setOutput("NextLocation", NextLocation);

  ROS_INFO("Sending goal %f %f", NextLocation.x, NextLocation.y);

  ROS_INFO("Target reached");

  return BT::NodeStatus::SUCCESS;
}
