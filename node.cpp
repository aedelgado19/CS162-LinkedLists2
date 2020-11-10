//created by Pranav Sharma

#include "Node.h"
Node::Node(Student* ptr1) {
  /*value = new Student();
  value = ptr1;
  ptr = NULL;
  */

  //NOTE: the above code given does not logically make sense.
  //edit by Allison:
  studentPtr = ptr1;
}


Node::~Node() {
  delete studentPtr;
  //  delete ptr;
}

Student* Node::getStudent() {
  //  return value;
  return studentPtr;

  /*edit by Allison: 

    previously, this function getStudent() returned the value of student (not ptr)
    I changed the function to return pointer
    since that is what the project desc. was for LLL pt 1
  */
}

Node* Node::getNext() {
  return next;
  //return ptr;
}

void Node::setNext(Node* nextNode) {
  next = nextNode;
}

void Node::setStudent(Student *inputStudent){
  studentPtr = inputStudent;

}
