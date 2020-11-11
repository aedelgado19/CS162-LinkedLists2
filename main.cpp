/* Author: Allison Delgado 
 * Contributor: Pranav Sharma (node.h and node.cpp)
 * Last updated: November 9, 2020
 */

#include <iomanip>
#include <iostream>
#include "node.h"
#include <cstring>
using namespace std;

//function prototypes
void addStudent(Node* head, Student *student);
void print(Node* &head);
void deleteStudent(Node* current, int id);
void Average(Node* next, float total, int count);
bool checkID(int id, Node* &head);
void quit();

//prints out goodbye message
void quit(){
  cout << "Now quitting program. Goodbye!" << endl;
}

//prints average GPA of all students to 2 decimal places
void Average(Node* next, float total, int count){
  float avg = 0.00;
  Node *traverse = next;
  if(traverse != NULL){
    count++; //increase count
    total += traverse->getStudent()->getGPA(); //add GPA's to toal
    //recursively call function
    Average(traverse->getNext(), total, count);
  } else {
    //print out average once hit end of list
    avg = total/count;
    cout << "Average GPA: " << fixed << setprecision(2) << avg << endl;
  }
}

//checks if ID is unique (example, cannot have 2 students with ID 1).
//returns bool true if ID is unique, false if not unique ID
bool checkID(int id, Node* &head){
  Node *traverse = head;
  if(traverse == NULL){ //first node in list will always be unique
    return true;
  }
  while(traverse->getNext() != NULL){
    traverse = traverse->getNext(); //traverse through list
    if(traverse->getStudent()->getID() == id){
      return false; //if id found matches inputted id, not unique
    }
  }
  return true;
}

//remove a node from the list
void deleteStudent(Node* current, int id){
  Student *studentPtr = NULL;
  if(current->getNext() != NULL){ //while not hit end of list
    studentPtr = current->getNext()->getStudent(); //create student pointer to access ID and other contents
    if(studentPtr->getID() == id){ //found matching id
      Node *deletenode = current->getNext(); //temporary holder to delete the node
      cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;
      current->setNext(deletenode->getNext());
      delete deletenode;
    } else {
      deleteStudent(current->getNext(), id); //recursively call delete to traverse thru list
    }
  } else { //current IS null
    cout << "Error: unknown student. " << endl;
  }
}



//add a new student to linked list
void addStudent(Node* head, Student *student){
   //this function is only called if head is not null
   Node* current = head;
   //Node* prev = NULL;

   if (current->getNext() == NULL || current->getNext()->getStudent()->getID() > student->getID()) {
     Node* temp = current->getNext();
     Node* newnode = new Node(student);
     newnode->setNext(temp);
     current->setNext(newnode);
   }
   else {
     addStudent(current->getNext(), student);
   }
}

//print out list
void print(Node* &head){
  Node *ptr = head;
  Student *studentPtr = NULL;
  
  if(ptr != NULL){
    studentPtr = ptr->getStudent(); //set student pointer to the student in the node
    cout << studentPtr->getFirstName() << " " << studentPtr->getLastName() //print out its contents
	 << ", " << studentPtr->getID() << ", " << fixed << setprecision(2) << studentPtr->getGPA() << endl;
    ptr = ptr->getNext(); //increment pointer to find next node
    print(ptr); //recursively call print function passing in incremented node
  }
}


int main(){
  Node* head = NULL; //beginning of list
  Node *prev = NULL;
  char input[10]; //holds either add, print, quit, average, or delete
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
      unique = checkID(id, head); //run through checkID function to make sure giving unique ID
      if(unique == true){ //if it is unique, then add proceed and add student
	student->setID(id);
	cout << "Enter the GPA of the student. " << endl;
	cout << " > "; //prompt input
	cin >> gpa;
	cin.get();
	student->setGPA(gpa);
	if(head == NULL){ //create head if first time through
	  head = new Node(student);
	}
	else if (id < head->getStudent()->getID()) {
	  Node* temp = head;
	  head = new Node(student);
	  head->setNext(temp);
	}
	else { //not head
	//call add student, which will recursively call itself to store student in order of least to greatest id
	  addStudent(head, student);
	}
      }
      else { //they entered an ID that is preexisting, delete progress of adding student
	cout << "That was not a unique student ID. Cannot add student. " << endl;
	delete student;
      }
    }
    //call print function passing in head
    else if(strcmp(input, "PRINT") == 0){
      if(head!=NULL){
	print(head);
      }
      else { //empty list
	cout << " There is nothing in the list!"  << endl;
      }
    }

    //delete a node
    else if(strcmp(input, "DELETE") == 0){
      int id = 0;
      //get id of requested delete
      cout << "What is the ID of the student you would like to delete? " << endl;
      cin >> id;
      cin.get();
      if(head == NULL){ //case: user tries to delete list but there is nothing in the list	
	cout << "Error: There is no student to delete!" << endl;
      } else { //head is not null
	Student *studentPtr = head->getStudent();

	//case: student id matches id of head, and there is nothing after it 
	if(studentPtr->getID() == id && head != NULL && head->getNext() == NULL){ 
	  cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;
	  Node *temp = head;
	  head = NULL;
	  delete temp;
	}

	//case: student id matches id of head, but there are more nodes after
	else if(studentPtr->getID() == id && head != NULL && head->getNext() != NULL){
	  cout << "now deleting " << studentPtr->getFirstName() << " " << studentPtr->getLastName() << endl;
	  Node *temp = head; //create temp pointer to head
	  head = head->getNext(); //change head to the next one
	  delete temp; //delete original head
	}
	
	else { //case: id does not match head
	  deleteStudent(head, id);
	}
      } 
    }
    //print out average of all GPA's
    else if(strcmp(input, "AVERAGE") == 0){
      Average(head, 0, 0); //Average() takes in (Node* next, float total, int count)
    }
  } //end while
  quit();

}
