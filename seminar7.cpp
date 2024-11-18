#include<iostream>
using namespace std;


class Student {

private:
	const int id;
	char* name;
	int age;

	//constructor fara parametrii
	Student() :id(0) {
		this->name = new char[strlen("N/A") + 1];
		strcpy(this->name, "N/A");
		this->age = 18;
		noStudents++;
	}

public:
	static int noStudents;

	//constructor cu ALL parametrii (sau partial)
	Student(const char* name, int age = 18) :id(noStudents) {
		if (age <= 0 || name == NULL || strlen(name) == 0) {
			//throw "incorrect params";
			throw new exception("incorrect params");
		}
		else {
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
			this->age = age;
			noStudents++;
		}
	}

	//getters:

	char* getName() {
		char* copieNumme = new char[strlen(this->name) + 1];
		strcpy(copieNumme, this->name);
		return copieNumme;//DEEP COPY :create a new zone of memory in heap where I store a copy of the value "name" and return the new address
	}
	int getAge() {
		return this->age;
	}
	//setter:
	void setName(const char* name) {
		if (this->name != NULL) {
			delete[] this->name;
			this->name = nullptr;
		}
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

	}

	//destructor
	~Student() {
		if (this->name != NULL) {
			delete[]this->name;
			this->name = nullptr;
		}
	}

};

int Student::noStudents = 0; //init static attributes

int main() {
	try {

		//To do:
		Student s1("Mada", 25);
		Student s2("Alex");

		cout << "\n->Create s3 based on s2 obj";
		Student s3(s2); // !!

		//verify 
		cout << "\nName s3: " << s3.getName();
		cout << "\n->Set new value for s3.name";
		s3.setName("Alex2");
		cout << "\nname s3: " << s3.getName();
		cout << "\ns2.name(should be the initial one):" << s2.getName();
		cout << endl << endl;

	}
	catch (const char* err) {
		cout << "\nError: " << err;
	}
	catch (exception* err) {
		cout << "\nError: " << err->what();
	}
	catch (...) {
		cout << "\nError: unknown error";
	}


	return 0;
}