/* Author: Allison Delgado 
 * Contributor: Pranav Sharma (node.h and node.cpp)
 * Last updated: November 8, 2020
 */

/*
TODO: 
- use recursion for GPA 2 decimal places
- write delete, fix up links, use a destructor, and watch out for if have empty list
- add checks for if something is valid, especially student ID
- add "average" function which prints GPA avg of all students to 2 dec places
- add comments
 */

#include <iostream>
#include "Node.h"
#include <cstring>
using namespace std;

//function prototypes
void addStudent(Node* &head);
void print(Node* &head);
void deleteStudent(Node* &head);
void Average(Node* &head);

void Average(Node* &head){
  
  //recursion!
}

void deleteStudent(Node* &head){
  Node *ptr = head;
  Node *prev = NULL;
  Student *studentPtr = NULL;
  int id = 0;
  char yn = 'y';
  if(ptr != NULL){
    prev = ptr;
    cout << "What is the ID of the student you would like to delete? " << endl;
    cin >> id;
    studentPtr = ptr->getStudent();
    if(studentPtr->getID() == id){
      cout << studentPtr->getFirstName() << " " << studentPtr->getLastName()
	   << ", " << studentPtr->getID() << " " << studentPtr->getGPA() << endl;
      cout << "Would you really like to delete this student? (y/n)" << endl;
      cin >> yn;
      if(yn == 'y' || yn == 'Y'){
	cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;

	//link up chain once deleted
	prev->next = ptr->next;
	ptr->next = NULL;
	delete ptr; //call contructor to delete that node
      }
      else{
	prev = ptr->next; //incrememnt previous
	deleteStudent(ptr->next); //recursively call function
	cout << "not deleting. " << endl;
      }
    }
  }
  else {
    cout << "no students are in the list yet!" << endl;
  }
  //head -> 1 -> 2 -> 3 -> end
}


//add a new student to linked list
void addStudent(Node* &head){
  char fName[50];
  char lName[50];
  int id = 0;
  float gpa = 0.00;
  Student* student = new Student();
  
  cout << "Enter the first name of student. " << endl;
  cout << " > "; //prompt input
  cin.get(fName, 50);
  cin.get();
  student->setFirstName(fName);
  cout << "Enter the last name of student. " << endl;
  cout << " > "; //prompt input
  cin.get(lName, 50);
  cin.get();
  student->setLastName(lName);
  cout << "Enter the student ID of the student. " << endl;
  cout << " > "; //prompt input
  cin >> id;
  cin.get();
  student->setID(id);
  cout << "Enter the GPA of the student. " << endl;
  cout << " > "; //prompt input
  cin >> gpa;
  cin.get();
  student->setGPA(gpa);
  
  //add into node
  Node* current = head;

  //first pass thru, no nodes yet
  if(current == NULL){
    head = new Node(student);
    head->setStudent(student);
    head->setNext(NULL); 
  }
  else {
    current = head;
    while(current->getNext() != NULL){
      current = current->getNext(); //traverse through by setting current to next
    }
    current->setNext(new Node(student));
    current->getNext()->setNext(NULL);
  }
}

//print out list
void print(Node* &head){
  Node *ptr = head;
  Student *studentPtr = NULL;

  if(ptr != NULL){
    studentPtr = ptr->getStudent();
    cout << studentPtr->getFirstName() << " " << studentPtr->getLastName()
	 << ", " << studentPtr->getID() << ", " << studentPtr->getGPA() << endl;
    ptr = ptr->getNext();
    print(ptr);
  }
}


int main(){

  Node* head = NULL; //beginning of list
  char input[10]; //holds either add or print currently
  cout << "Welcome to (Linked) StudentList. " << endl;
  cout << "To add a student, type 'ADD'." << endl;
  cout << "To print out list, type 'PRINT'." << endl;
  cout << "To delete a student, type 'DELETE'." << endl;
  cout << "To average all student GPA's, type 'AVERAGE'." << endl;
  cout << "To quit, type 'QUIT'." << endl;
  //while they havent quit..
  while(strcmp(input, "QUIT") != 0){
    cout << "Enter a command (ADD/PRINT/DELETE/AVERAGE/QUIT)" << endl;
    cout << " > "; //prompt user again
    cin.get(input, 10);
    cin.get();

    //make to uppercase
    for(int i = 0; i < strlen(input); i++){
      input[i] = toupper(input[i]);
    }

    //call respective functions
    if(strcmp(input, "ADD") == 0){
      addStudent(head);
    }
    else if(strcmp(input, "PRINT") == 0){
      print(head);
    }
    else if(strcmp(input, "DELETE") == 0){
      deleteStudent(head);
    }
    else if(strcmp(input, "AVERAGE") == 0){
      Average(head);
    }
  }
  cout << "Now quitting. Goodbye! " << endl;
}
