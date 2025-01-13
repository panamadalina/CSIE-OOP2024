#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Person Class Definition
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

    // Destructor
    ~Person() {
        if (this->name != NULL) {
            cout << "\n[Person] Calling...destruct ...";
            delete[] this->name;
            this->name = nullptr;
        }
    }

    // Assignment Operator Overload
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

    void serialization() {
        //
        ofstream f("person.bin", ios::binary);
        int length = strlen(this->name);//.length();
        f.write((char*)&length, sizeof(length));

        f.write(this->name/*.c_str()*/, length + 1);
        f.write((char*)&this->age, sizeof(this->age));
       /* f.write((char*)&this->noGrades, sizeof(this->noGrades));
        for (int i = 0; i < noGrades; i++) {
            f.write((char*)&this->Grades[i], sizeof(this->Grades[i]));
        }*/

		cout << "\nDone!";
        f.close();
    }
    void deserialization() {
        ifstream f("person.bin", ios::binary);
        int dimname;
        f.read((char*)&dimname, sizeof(int));
        char* aux = new char[dimname + 1];
        f.read(aux, dimname + 1);
        //this->name = aux;
		this->name = new char[dimname + 1];
		strcpy(this->name, aux);
        delete[] aux;//!
        f.read((char*)&this->age, sizeof(this->age));
        //	int dimnoGrades;//!!!!
        //	f.read((char*)&dimnoGrades, sizeof(dimnoGrades));//!Wrong!
        //f.read((char*)&this->noGrades, sizeof(this->noGrades));//need it first
        //this->Grades = new int[this->noGrades];
        //for (int i = 0; i < this->noGrades; i++) {
        //    f.read((char*)&this->Grades[i], sizeof(this->Grades[i]));
        //}
        cout << "\nDone!";
        f.close();
    }

    friend ostream& operator<<(ostream& out, Person& p);
};

// Overloading << for Person
ostream& operator<<(ostream& out, Person& p) {
    out << "\nPerson: " << p.name << ", age: " << p.age;
    return out;
}

// Student Class Definition
class Student : public Person {
    char* university;

public:
    // Default Constructor
    Student() : Person() {
        cout << "\n[Student] Calling...Constr without params ...";
        this->university = 0;
    }

    // Parameterized Constructor
    Student(const char* name, int age, const char* university) : Person(name, age) {
        cout << "\n[Student] Calling...Constr with params ...";
        this->university = new char[strlen(university) + 1];
        strcpy(this->university, university);
    }


	// Copy Constructor
	Student(const Student& s) : Person(s) {
		cout << "\n[Student] Calling...Copy constr ...";
		this->university = new char[strlen(s.university) + 1];
		strcpy(this->university, s.university);
	}

	// Operator =
	Student& operator=(const Student& s) {
		Person::operator=(s);
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
    //Person p = s;
	//out << p;

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
	Student s2 = s1;
	cout << "\nS2:\n" << s2;

    cout << "\n-------------------\n";
	Student s3;
	s3 = s1; 
	cout << "\nS3:\n" << s3;

	cout << "\n-------------------\n";
	Person p1("Mihai", 21);
	p1.serialization();
	Person p2;
	p2.deserialization();
	cout << "\nP Copy:\n" << p2;
    return 0;
}