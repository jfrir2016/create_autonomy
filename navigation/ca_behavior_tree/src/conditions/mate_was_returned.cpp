#include <ca_behavior_tree/conditions/mate_was_returned.h>


BT::NodeStatus MateWasReturned::tick()
{
  static int i = 0;      
  if (i <= 3)
  {
    i++;
    return BT::NodeStatus::FAILURE;
  }
  i = 0;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList MateWasReturned::providedPorts()
{
  return
  {
  };
}