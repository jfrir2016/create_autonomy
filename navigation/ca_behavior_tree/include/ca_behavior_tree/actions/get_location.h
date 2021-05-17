/**
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2020, Emiliano Borghi
 *
 */
#ifndef CA_BEHAVIOR_TREE_ACTIONS_GETLOC_CLIENT_H
#define CA_BEHAVIOR_TREE_ACTIONS_GETLOC_CLIENT_H

#include <string>

#include <ros/ros.h>
#include <tf/transform_datatypes.h>

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

#include <behaviortree_cpp_v3/action_node.h>

#include "ca_behavior_tree/actions/movebase_client.h"


//----------------------------------------------------------------

namespace BT
{
}  // end namespace BT

class GetLoc : public BT::AsyncActionNode
{
public:
  GetLoc(const std::string& name, const BT::NodeConfiguration& config)
    : BT::AsyncActionNode(name, config)
  {
  }

  static BT::PortsList providedPorts()
  {
    return
    {
      BT::OutputPort<Pose2D>("NextLocation"),
    };
  }

  BT::NodeStatus tick() override;


private:

};

#endif  // CA_BEHAVIOR_TREE_ACTIONS_MOVEBASE_CLIENT_H
