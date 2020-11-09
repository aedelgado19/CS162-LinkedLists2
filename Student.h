#include <iostream>
class Student{
public:
  Student* getStudent();
  void setFirstName(char* inputName);
  char* getFirstName();
  void setLastName(char* inputName);
  char* getLastName();
  void setID(int inputID);
  int getID();
  void setGPA(float inputGPA);
  float getGPA();
  
  Student();
  ~Student();
private:
  char fName[50];
  char lName[50];
  int id;
  float gpa;
};
