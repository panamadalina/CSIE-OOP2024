#include<iostream>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

class Student {
    int age;
    char* name; 	//heap: dynamic memory
    int* grades; 	//heap: dynamic memory
    //char [] name;//STACK
public:
    //default constr
    Student() { //no input params
        cout << "\n Default constructor is called..";
        this->age = 18;
        this->name = new char[strlen("N/A") + 1];
        strcpy(this->name, "N/A");
        this->grades = new int[10];
    }
    //constructs with ALL parameters
    Student(const char* name, int age = 18) {
        cout << "\n Constructor with Params is called..";
        this->age = age;
        this->name = new char[strlen(name) + 1];
        this->grades = new int[10];
        strcpy(this->name, name);
    }
    //constructs with parameters (part of the parameters)
    //Student(const char* name) {
    //    cout << "\n Constructor with Params is called..";
    //    this->age = 18;
    //    //this->grades = new int[10];
    //    this->name = new char[strlen(name) + 1];
    //    strcpy(this->name, name);
    //}

    // 1. getter 
    int getAge() {
        return this->age;
}
    const char* getName(){
        if (this->name != NULL) {
            return this->name;
        }
        else return "Not INIT";
    }
     //2. setter
      void setAge(int age) {
            this->age = age;
	  }
	  void setName(const char* name) {
		  if (this->name != NULL) {
			  delete[] this->name;
			  this->name = nullptr;
		  }
		  this->name = new char[strlen(name) + 1];
		  strcpy(this->name, name);
	  }
      void printDetails() {//behaviour
          cout << "\nStudent "<< this->getName()<<" has age "<<this->getAge();
      }
	  //destructor
      ~Student() {
            cout << "\n Default DEstructor is called..";
			if (this->name != NULL) {
				delete[] this->name;
				this->name = nullptr;
			}
			if (this->grades != NULL) {
				delete[] this->grades;
				this->grades = nullptr;
			}
	  }
};

int main() {
   
	Student s("John", 20);
    Student s1; //declaration+default init
    //s1.Student();
    //s1.printDetails()
    cout << "\n" << s1.getAge();
    s1.setAge(20);
	cout << "\n" << s1.getAge();
    s1.setName("Madalina");
	s1.printDetails();
    
    //THIS pointer= standard name, its storing address of the object
    //char* name = new char[3];
    //delete[] name;
    Student s2("Madalina", 24);
    s2.printDetails();
    
    //this function is used to check for memory leaks:
	_CrtDumpMemoryLeaks();//in Output window we still see memory leaks
	//this function is not working for classes with dynamic memory
	//cannot detected that the memory will be deleted by the destructor
	//because this function is triggered before the destructor is called
    
    return 0;
}