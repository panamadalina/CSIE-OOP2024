#include<iostream>

using namespace std;

class Student {

private:
	const int id;
	char* name;
	int age;

public:
	static int noStudents;

	//constructor fara parametrii
	Student() :id(0) {
		this->name = new char[strlen("N/A") + 1];
		strcpy(this->name, "N/A");
		this->age = 18;
		noStudents++;
	}
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
	//constructor with params (partial)
	/*Student(const char* name) :id(0) {
		if (age <= 0 || name == NULL || strlen(name) == 0) {
		throw "incorrect params";
		}
		else {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = 20;
		}

	}*/

	//getters:
	char* getNameShallowCopy() {
		return this->name;//SHALLOW COPY: Return address where is located name in HEAP
	}
	char* getNameDeepCopy() {
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
		//Student s("", 25);
		Student s1("Mada", 25);
		Student s2("Alex");

		cout << "\n->Create s3 based on s2 obj";

		//verify shallow copy for getName() 
		char* nameStudShallowCopy = s2.getNameShallowCopy();
		cout << "\nnameStudShallowCopy:" << nameStudShallowCopy;
		//nameStud = new char[strlen("Maria") + 1]; //nu realoc memorie
		cout << "\n->Set new value for nameStudShallowCopy";
		strcpy(nameStudShallowCopy, "Mari");
		cout << "\nnameStudShallowCopy:" << nameStudShallowCopy;
		cout << "\ns2.name(shallow copy):" << s2.getNameShallowCopy();
		cout << endl << endl;
		//daca stergem nameStudShallowCopy se va sterge si s2.name

		//verif deep copy for getName()

		char* nameStudDeepCopy = s2.getNameDeepCopy();
		cout << "\nnameStudDeepCopy:" << nameStudDeepCopy;
		cout << "\n->Set new value for nameStudDeepCopy";
		strcpy(nameStudDeepCopy, "Ana");
		cout << "\nnameStudDeepCopy:" << nameStudDeepCopy;
		cout << "\ns2.name(deep copy):" << s2.getNameShallowCopy();
		delete[] nameStudDeepCopy;
		cout << endl << s2.getNameDeepCopy();//here I lost the address of the memory zone created and I can't deallocate it at the end

		/*
		Rule! Any class that has pointer members must contain:
		- constructors
		- destructor
		- copy constructor
		- overload op =
		*/

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