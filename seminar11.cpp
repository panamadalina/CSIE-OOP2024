#include <iostream>
using namespace std;

class Person {
    char* name;
    int age;

protected:
    int test;

public:
    int cnp;

    // Default Constructor
    Person() {
        cout << "\n[Person] Calling...Constr without params ...";
        this->name = new char[strlen("N/A") + 1];
        strcpy(this->name, "N/A");
        this->age = 18;
    }

    // Parameterized Constructor
    Person(const char* name, int age) {
        if (age <= 0 || name == NULL || strlen(name) == 0) {
            throw new exception("incorrect params");
        }
        else {
            cout << "\n[Person] Calling...Constr with params ...";
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
            this->age = age;
        }
    }

    // Copy Constructor
    Person(const Person& s) {
        cout << "\n[Person] Calling...Copy constr ...";
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->age = s.age;
    }

    // Op=
    Person& operator=(const Person& s) {
        cout << "\n[Person] Calling...Op = ...";
        if (this->name != NULL) {
            delete[] this->name;
            this->name = nullptr;
        }
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->age = s.age;
        return *this;
    }

    // Getters
    char* getName() {
        cout << "\n[Person] Calling...Get name ...";
        char* copieNumme = new char[strlen(this->name) + 1];
        strcpy(copieNumme, this->name);
        return copieNumme;
    }

    int getAge() {
        cout << "\n[Person] Calling...Get age ...";
        return this->age;
    }

    // Setters
    void setName(const char* name) {
        cout << "\n[Person] Calling...Set name ...";
        if (this->name != NULL) {
            delete[] this->name;
            this->name = nullptr;
        }
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // Destructor
    ~Person() {
        if (this->name != NULL) {
            cout << "\n[Person] Calling...destruct ...";
            delete[] this->name;
            this->name = nullptr;
        }
    }
    friend ostream& operator<<(ostream& out, Person& p);
};

// Overloading << for Person
ostream& operator<<(ostream& out, Person& p) {
    out << "\nPerson: " << p.name << ", age: " << p.age;
    return out;
}

// Student Class 
class Student : public Person {
    char* university;

public:
    // Default Constructor
    Student() : Person() {
        cout << "\n[Student] Calling...Constr without params ...";
        this->university = 0;
    }

    // Constructor with params
    Student(const char* name, int age, const char* university) : Person(name, age) {
        cout << "\n[Student] Calling...Constr with params ...";
        this->university = new char[strlen(university) + 1];
        strcpy(this->university, university);
    }


	// Copy Constructor
	Student(const Student& s) {
		this->university = new char[strlen(s.university) + 1];
		strcpy(this->university, s.university);
	}

	// Operator =
	Student& operator=(const Student& s) {
		cout << "\n[Student] Calling...Op = ...";
		if (this->university != NULL) {
			delete[] this->university;
			this->university = nullptr;

		}
		this->university = new char[strlen(s.university) + 1];
		strcpy(this->university, s.university);
		return *this;
	}




    // Destructor
    ~Student() {
		if (this->university != NULL) {// only university is allocated dinamically
            cout << "\n[Student] Calling...destruct ...";
            delete[] this->university;
            this->university = nullptr;
        }
    }



    friend ostream& operator<<(ostream& out, Student& s);
};

// Overloading << for Student
ostream& operator<<(ostream& out, Student& s) {

	out << "\nStudent: " << s.getName() << ", age: " << s.getAge();
    out << " is at university: " << s.university;
    return out;
}

int main() {

   // Person p;
   // cout << p;
	cout << "\n-------------------\n";
	Student s1("Mada", 20, "UBB");

    cout << "\nS1:\n" << s1;

    cout << "\n-------------------\n";
	//Student s2 = s1;
	//cout << "\nS2:\n" << s2;

 //   cout << "\n-------------------\n";
	//Student s3;
	//s3 = s1; 
	//cout << "\nS3:\n" << s3;

    return 0;
}