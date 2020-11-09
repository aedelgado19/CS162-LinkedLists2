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
//bool checkID(int id, Node* &head);


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
/*
//THIS DOESNT WORK ALLY!!!!!!!!!!!!!!!!!!!!!!!!!!
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
*/
void deleteStudent(Node* current, int id){
  Node *ptr = current;
  //  Node *prev = NULL;
  Node *prev = NULL;
  Student *studentPtr = NULL;
  char yn = 'y';
  cout << "What is the ID of the student you would like to delete? " << endl;
  cin >> id;
  studentPtr = ptr->getStudent();
  if(studentPtr->getID() == id){
    cout << studentPtr->getFirstName() << " " << studentPtr->getLastName()
	 << ", " << studentPtr->getID() << " " << studentPtr->getGPA() << endl;
    cout << "Would you really like to delete this student? (y/n)" << endl;
    if(yn == 'y' || yn == 'Y'){
      cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;
      ptr->next = ptr->next->next;
      ptr->next->next = NULL;
      delete studentPtr;
    }
    else{
      cout << "not deleting. " << endl;
    }
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
	  deleteStudent(ptr->next, id); //recursively call function
	  cout << "not deleting. " << endl;
	}
      }
    }
  }

   else {
     cout << "no students are in the list yet!" << endl;
   }
   //head -> 1 -> 2 -> 3 -> end
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
    print(ptr);
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
      /*unique = checkID(id, head);
	if(unique == true){*/
      student->setID(id);
      /*}
	else {
	cout << "That was not a unique student ID. Cannot add student. " << endl;
	delete student;
	}*/
      cout << "Enter the GPA of the student. " << endl;
      cout << " > "; //prompt input
      cin >> gpa;
      cin.get();
      student->setGPA(gpa);
      if(head == NULL){
	head = new Node(student);
      } else {
	addStudent(head, student);
      }
    }
    else if(strcmp(input, "PRINT") == 0){
      print(head);
    }
    else if(strcmp(input, "DELETE") == 0){
      deleteStudent(head, 0);
    }
    else if(strcmp(input, "AVERAGE") == 0){
      Average(head, 0, 0);
    }
  }
  cout << "Now quitting. Goodbye! " << endl;

}
