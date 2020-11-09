//header file for node created by Pranav Sharma
#pragma once
#include <iostream>
#include "Student.h"
class Node
{
public:
  // variables in Node class
  Student* value;
  Node* ptr;
  // gets the next node in the linked list
  Node* getNext();
  // gets the student that the node contains
  Student* getStudent();
  // sets next node in the linked list
  void setNext(Node* ptr1);
  // constructer and destructors, initializes and deletes pointers
  Node(Student* value);
  ~Node();
  Node *next;
  //additions by me (Allison):
  void setStudent(Student *inputStudent);
private:
  Student *studentPtr;

};
