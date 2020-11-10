/* Author: Allison Delgado 
 * Contributor: Pranav Sharma (node.h and node.cpp)
 * Last updated: November 8, 2020
 */

/*
TODO: 

- write delete, fix up links, use a destructor, and watch out for if have empty list
- add checks for if something is valid, especially student ID
- add comments
 */
#include <iomanip>
#include <iostream>
#include "Node.h"
#include <cstring>
using namespace std;

//function prototypes
void addStudent(Node* head, Student *student);
void print(Node* &head);
void deleteStudent(Node* current, int id);
void Average(Node* next, float total, int count);
bool checkID(int id, Node* &head);


void Average(Node* next, float total, int count){
  float avg = 0.00;
  Node *traverse = next;
  if(traverse != NULL){
    count++;
    total += traverse->getStudent()->getGPA();
    //recursively call function
    Average(traverse->getNext(), total, count);
  } else {
    avg = total/count;
    cout << "Average GPA: " << fixed << setprecision(2) << avg << endl;
  }
}

bool checkID(int id, Node* &head){
  cout << "check id" << endl;
  Node *traverse = head;
  if(traverse == NULL){ //first node in list
    return true;
  }
  while(traverse->next != NULL){
    cout << "in loop" <<endl;
    traverse = traverse->getNext();
    cout << "\nA";
    cout << traverse->getStudent()->getID() << endl;
    cout << "\nB";
    if(traverse->getStudent()->getID() == id){
      cout << "\nC";
      return false;
    }
    cout << "\nD";
  }
  return true;
}

void deleteStudent(Node* current, int id){
  Node *ptr = current;
  Student *studentPtr = NULL;
  char yn = 'y';
  if(ptr->getNext() != NULL){
    studentPtr = ptr->getNext()->getStudent();
    if(studentPtr->getID() == id){
	cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;
	ptr->setNext(ptr->getNext());
	delete studentPtr;
      }
    } else {
      deleteStudent(current->getNext(), id); //recursively call delete to traverse thru list
    }
  } else { //current IS null
      cout << "no students are in the list yet!" << endl;
  }
}



//add a new student to linked list
void addStudent(Node* head, Student *student){
  
  //add into node
  Node* current = head;

  if(current->getNext() == NULL){ //find end of list
    current->setNext(new Node(student));
  }
  else { //recursively call function again
    addStudent(head->getNext(), student);
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
    print(ptr); //recursively call print function
  }
}


int main(){
  Node* head = NULL; //beginning of list
  Node *prev = NULL;
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
      char fName[50];
      char lName[50];
      int id = 0;
      float gpa = 0.00;
      Student* student = new Student();
      bool unique = true;
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
      unique = checkID(id, head);
      if(unique == true){
	student->setID(id);
      }
      else {
	cout << "That was not a unique student ID. Cannot add student. " << endl;
	delete student;
      }
      cout << "Enter the GPA of the student. " << endl;
      cout << " > "; //prompt input
      cin >> gpa;
      cin.get();
      student->setGPA(gpa);
      if(head == NULL){
	head = new Node(student);
      } else {
	 //call add student, which will recursively call itself to find end of list
	addStudent(head, student);
      }
    }
    else if(strcmp(input, "PRINT") == 0){
      if(head!=NULL){
	print(head);
      }
      else {
	cout << " There is nothing in the list!"  << endl;
      }
    }
    else if(strcmp(input, "DELETE") == 0){
      int id = 0;
      cout << "What is the ID of the student you would like to delete? " << endl;
      cin >> id;
      cin.get();
      if(head == NULL){ //case: user tries to delete list but there is nothing in the list	
	cout << "Error: There is no student to delete!" << endl;
      } else { //head is not null
	Student *studentPtr = head->getStudent();

	//case: student id matches id of head, and there is nothing after it 
	if(studentPtr->getID() == id && head != NULL && head->getNext() == NULL){ 
	  Node *temp = head;
	  head = NULL;
	  delete temp;
	}

	//case: student id matches id of head, but there are more nodes after
	else if(studentPtr->getID() == id && head != NULL && head->getNext() != NULL){
	  Node *temp = head; //create temp pointer to head
	  head = head->getNext(); //change head to the next one
	  delete temp; //delete original head
	}
	
	else { //case: id does not match head
	  deleteStudent(head, id);
	}
      } 
    }
    else if(strcmp(input, "AVERAGE") == 0){
      Average(head, 0, 0);
    }
    
  }
  cout << "Now quitting. Goodbye! " << endl;

}
