#ifndef CA_BEHAVIOR_TREE_CONDITIONS_MATE_WAS_RETURNED_OK_H
#define CA_BEHAVIOR_TREE_CONDITIONS_MATE_WAS_RETURNED_OK_H

#include <string>

#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/condition_node.h>

#include <ros/ros.h>
#include <std_msgs/Float32.h>


class MateWasReturned : public BT::ConditionNode
{
private:
  // The node that will be used for any ROS operations
public:
  MateWasReturned(const std::string& name, const BT::NodeConfiguration& config) : BT::ConditionNode::ConditionNode(name, config) {

  }
  ~MateWasReturned(){}
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
};

#endif