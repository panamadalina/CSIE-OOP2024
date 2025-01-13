#include<iostream>
using namespace std;

class Student {
private:
    char* name;
    int age;
    char* university;

public:
    // Default constructor
    Student() {
        cout << "\n~Default constructor->Student: Anonymous";
        this->name = new char[strlen("Anonymous") + 1];
        strcpy(this->name, "Anonymous");
        this->age = 0;
        this->university = new char[strlen("Unknown") + 1];
        strcpy(this->university, "Unknown");
    }

    // Constructor with params
    Student(const char* name, int age, const char* university) : age(age) {
        cout << "\n~Construct with params->Student: " << name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->university = new char[strlen(university) + 1];
        strcpy(this->university, university);
    }

    // Copy constructor
    Student(const Student& s) {
        cout << "\n~Copy constructor->Student: " << s.name;
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->age = s.age;
        this->university = new char[strlen(s.university) + 1];
        strcpy(this->university, s.university);
    }

    // Assignment operator
    Student& operator=(const Student& s) {
        cout << "\n~Operator= ->Student: " << s.name;
        if (this->name != NULL) {
            delete[] this->name;
        }
        if (this->university != NULL) {
            delete[] this->university;
        }
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        this->age = s.age;
        this->university = new char[strlen(s.university) + 1];
        strcpy(this->university, s.university);
        return *this;
    }

    // Destructor
    ~Student() {
        cout << "\n~Destructor->Student: " << this->name;
        if (this->name != NULL) {
            delete[] this->name;
        }
        if (this->university != NULL) {
            delete[] this->university;
        }
    }

    // Getters
    char* getName() const {
		char* copy = new char[strlen(this->name) + 1];
		strcpy(copy, this->name);
		return copy;
    }

    int getAge() const {
        return this->age;
    }

    char* getUniversity() const {
        return this->university;
    }
    //op<<
    friend ostream& operator<<(ostream& out, const Student& s);
};

ostream& operator<<(ostream& out, const Student& s) {
    out << "\nStudent " << s.getName() << " is " << s.getAge()
        << " years old and studies at: " << s.getUniversity();
    return out;
}
//Has-a relationship (1-n): professor->diploma, etc.
class Domain {
private:
    Student* studentList;
    int studentCount;
    char* name;

public:
    // Default constructor
    Domain() {
        this->name = new char[strlen("Unknown") + 1];
        strcpy(this->name, "Unknown");
        this->studentList = NULL;
        this->studentCount = 0;
    }

    // Parameterized constructor
    Domain(const char* name, Student* students, int count) {
        cout << "\n~Parameterized constructor->Domain: " << name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->studentList = new Student[count];
        this->studentCount = count;
        for (int i = 0; i < count; i++) {
            this->studentList[i] = students[i];
        }
    }

    // Destructor
    ~Domain() {
        if (this->name != NULL) {
            delete[] this->name;
        }
        if (this->studentList != NULL) {
            delete[] this->studentList;
        }
    }

    friend ostream& operator<<(ostream& out, const Domain& d);
};

ostream& operator<<(ostream& out, const Domain& d) {
    out << "\nIn domain: " << d.name << " we have the students: ";
    for (int i = 0; i < d.studentCount; i++) {
        out << d.studentList[i] << " ";
    }
    return out;
}

int main() {
    Student s1("Mada", 21, "CSIE");
    Student s2;
    s2 = s1;

    cout << s1;

    cout << endl << endl;
    Student s3("Alex", 22, "Politehnica");
    Student s4("Andrew", 24, "Informatics University");
    Student* studentList = new Student[3];
    studentList[0] = s1;
    studentList[1] = s3;
    studentList[2] = s4;

    cout << endl << endl;
    Domain d("IT", studentList, 3);
    cout << d;

    cout << endl << endl;

    delete[] studentList; // Free allocated memory for student list
    return 0;
}
