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
#include <std_msgs/String.h>


//----------------------------------------------------------------

using namespace std;

template <class T>

class Node
{
    public:
        Node();
        Node(T);
        ~Node();

        Node *next;
        T data;

        void delete_all();
        void print();
};

template <class T>

class List
{
    public:
        List();
        ~List();

        Node<T> *m_head;
        int m_num_nodes;

        void add_head(T);
        void add_end(T);
        void add_sort(T);
        void concat(List);
        void del_all();
        void del_by_data(T);
        void del_by_position(int);
        void fill_by_user(int);
        void fill_random(int);
        void intersection(List);
        void invert();
        void load_file(string);
        void print();
        void save_file(string);
        void search(T);
        void sort();
};

namespace BT
{
}  // end namespace BT

class GetLoc : public BT::AsyncActionNode
{
  private:
    int active_;
    List<int32_t> list;
    Pose2D Locations[10]{{-7.0,5.9,3.14},{-8.8,5.9,3.14},{-10.5,5.8,3.14},{-8.2,9.1,3.14},{-10.0,9.1,3.14},{-11.7,9.1,3.14},{-7.0,10.4,3.14},{-8.8,10.4,3.14},{-10.5,10.4,3.14}};
    Pose2D DefaultLoc = {-5.5,5.0,1.57};
    ros::Subscriber sub_;
  public:
    GetLoc(const std::string& name, const BT::NodeConfiguration& config);
    ~GetLoc();
    static BT::PortsList providedPorts()
    {
      return
      {
        BT::OutputPort<Pose2D>("NextLocation"),
      };
    }

    BT::NodeStatus tick() override;
};

typedef struct user_t
{
  string name;
  int location;
} user;

#endif  // CA_BEHAVIOR_TREE_ACTIONS_MOVEBASE_CLIENT_H
