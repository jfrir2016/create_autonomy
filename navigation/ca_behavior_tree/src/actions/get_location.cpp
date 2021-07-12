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
  active_ = 0;
  list = List<int>();
  ros::NodeHandle n;
  sub_ = n.subscribe<std_msgs::Float32>("/robomate/ui",1,[this](const std_msgs::Float32::ConstPtr& msg)
    {
      ROS_INFO("I heard: [%f]!!", msg->data);
      int loc = msg->data;
      if (loc > 0) {
        active_++;
        list.add_end(loc);
      }
      if (loc < 0) {
        active_--; 
        list.del_by_data(-loc);
      }  
    });
}

GetLoc::~GetLoc(){
  list.~List();
};

BT::NodeStatus GetLoc::tick()
{
  static int turn = 0;
  static Node<int> *temp;
  Pose2D NextLocation;
  
  // Take the pose from the list
  if (list.m_head != NULL) {
    ROS_INFO("Entre al if");
    //turn %= active_;
    //turn++;
    //ROS_INFO("Entre al if %d",turn);
    if (turn != 0 && temp != NULL && temp->next != NULL) {
      temp = temp->next;
    } else {
      temp = list.m_head;
      turn ++;
    }
    ROS_INFO("Data: %d", temp->data);
    NextLocation = Locations[(temp->data)-1];
  } else {
    turn = 0;
    return BT::NodeStatus::FAILURE;
    //NextLocation = DefaultLoc;
  } 
  setOutput("NextLocation", NextLocation);

  ROS_INFO("Sending goal %f %f", NextLocation.x, NextLocation.y);

  ROS_INFO("Target reached");

  return BT::NodeStatus::SUCCESS;
}

using namespace std;

// Constructor por defecto
template<typename T>
List<T>::List()
{
    m_num_nodes = 0;
    m_head = NULL;
}

// Insertar al inicio
template<typename T>
void List<T>::add_head(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = m_head;

    if (!m_head) {
        m_head = new_node;
    } else {
        new_node->next = m_head;
        m_head = new_node;
    }
    m_num_nodes++;
}

// Insertar al final
template<typename T>
void List<T>::add_end(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = m_head;
    new_node->next = m_head;

    if (!m_head) {
        m_head = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    m_num_nodes++;
}

// Eliminar por data del nodo
template<typename T>
void List<T>::del_by_data(T data_)
{
    Node<T> *temp = m_head;
    Node<T> *temp1 = m_head->next;

    int cont = 0;
    if (m_head == NULL) {
      cout << "No existe el dato " << endl;
      return;
    }  
    if (m_head->data == data_) {
        m_head = temp->next;
        cont = 1;
        ROS_INFO("Elimine el %d", data_);
    } else {
        while (temp1 != NULL && cont == 0) {
            if (temp1->data == data_) {
                ROS_INFO("Elimine el %d", data_);
                Node<T> *aux_node = temp1;
                temp->next = temp1->next;
                delete aux_node;
                cont = 1;
                m_num_nodes--;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
    }

    if (cont == 0) {
        cout << "No existe el dato " << endl;
    }
}

template<typename T>
List<T>::~List() {}

// Constructor por defecto
template<typename T>
Node<T>::Node()
{
    data = NULL;
    next = NULL;
}

// Constructor por parámetro
template<typename T>
Node<T>::Node(T data_)
{
    data = data_;
    next = NULL;
}

template<typename T>
Node<T>::~Node() {}