#include <iostream>
#include "Student.h"
#include <cstring>
using namespace std;

void Student::setFirstName(char* inputName){
  strcpy(fName, inputName);

}

char* Student::getFirstName(){
  return fName;
}

void Student::setLastName(char* inputName){
  strcpy(lName, inputName);

}

char* Student::getLastName(){
  return lName;
}
void Student::setID(int inputID){
  id = inputID;
}

int Student::getID(){
  return id;
}

void Student::setGPA(float inputGPA){
  gpa = inputGPA;

}

float Student::getGPA(){
  return gpa;
}

//constructor
Student::Student(){

}

Student::~Student(){
  
}
