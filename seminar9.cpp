//sem 9

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Student {

private:
	const int id; //unique with the static atribute NOSTUD
	char* name;
	int age;
	//int* grades;
	bool works;

	Student() :id(0) {
		this->name = new char[strlen("N/A") + 1];
		strcpy(this->name, "N/A");
		this->age = 18;
		noStudents++;
	}

public:
	static int noStudents;

	Student(const char* name, int age = 18) :id(noStudents) {
		cout << "\nCalling... constructor with params....\n";
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


	char* getName() {
		char* copieNumme = new char[strlen(this->name) + 1];
		strcpy(copieNumme, this->name);
		return copieNumme;
	}
	int getAge() {
		return this->age;
	}
	void setName(const char* name) {
		if (this->name != NULL) {
			delete[] this->name;
			this->name = nullptr;
		}
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);

	}
	Student(const Student& s) :id(noStudents) {
		cout << "\nCalling...Copy constructor....\n";
		this->name = new char[strlen(s.name) + 1];
		strcpy(this->name, s.name);
		this->age = s.age;
		noStudents++;

	}
	Student& operator=(const Student& s) {
		cout << "\nCalling...OP =....\n";
		if (this->name != NULL) {
			delete[] this->name;
			this->name = nullptr;
		}
		this->name = new char[strlen(s.name) + 1];
		strcpy(this->name, s.name);
		this->age = s.age;
		return *this;

	}

	~Student() {
		if (this->name != NULL) {
			delete[]this->name;
			this->name = nullptr;

		}
	}



	// cout<< s1;
	friend ostream& operator<<(ostream& out, const Student& s);

	// cin>>s1
	friend istream& operator>>(istream& in, Student& s);

	//cout<<s1[0]
	char operator[](int index) {
		return this->name[index];
	}

	//cout<<(int)s1
	/*operator int() {
		return this->age;
	}*/

	//if(!s1)
	//bool operator!() {
	//	//return !this->works;
	//	return this->age < 18;
	//}

	//----------------------------------------------------------------------------------------
	//Student operator!() {

	//	Student temp = *this;
	//	//temp.age = 18;
	//	temp.works = !temp.works;
	//	return *this;
	//}

	//++
	//1. post ++
	//s7 = s1++;

	const Student operator++(int i) {
		Student temp = *this;
		this->age++;
		return temp;
	}

	//2 . pre ++
	friend const Student operator++(Student& s); 

	//+= 
	Student operator+=(const Student& s) {
		this->age += s.age;  // integer += integer;
		return *this;
	}
	Student operator+=(int value) {
		this->age += value;  // integer += integer;
		return *this;
	}

	Student operator+ (const Student& s) {
		Student temp = *this;
		temp.age += s.age;
		return temp;
	}

	Student operator+ (int i) { 
		Student temp = *this;
		temp.age += i;

		return temp;
	}

	friend const Student operator+(int value, const Student& s);


	static int getNumberStudents() {

		return noStudents;
	}
	static bool checkEligibility() {
		//some condition 
		return noStudents;
	}

};

int Student::noStudents = 0; 

ostream& operator<<(ostream& out, const Student& s) {

	out << "\nThe student with id: " << s.id << " has the name: " << s.name << " and the age: " << s.age;
	return out;
}

istream& operator>>(istream& in, Student& s) {

	cout << "\nName: ";
	char temp[20];
	in >> temp;
	if (strlen(temp) != 0) {
		if (s.name != 0) {
			delete[] s.name;
			s.name = nullptr;
		}
		s.name = new char[strlen(temp) + 1];
		strcpy(s.name, temp);
	}


	cout << "\nAge: ";
	in >> s.age;

	return in;
}

//----------------------------------------------------------------------------------------

//pre ++
const Student operator++(Student& s) {
	s.age++;
	return s;
}

const Student operator+(int value, const Student& s) {
	Student temp = s;
	temp.age += value;

	return temp;
}

int main() {
	try {

		Student s1("Mada", 25);
		Student s2("Alex");

		cout << "\n->Create s3 based on s2 obj";
		Student s3(s2); //copy constructor is like Student s3 = s2;      

		s2 = s3; //op =


		Student s7("mada", 30);
		cout << endl << "\nOperator << " << endl;
		//cin >> s2; //op >>

		cout << endl << "\nOperator ++ -> POST" << endl;
		cout << s7++;// POST//age // s1.operator++() s1+1 s1.operator++(int)
		cout << endl << "\nOperator ++ -> PRE" << endl;
		cout << ++s7; //pre // s1.operator++()  //1+s1  int.operator++(s1)

		cout << endl << "\nOperator CAST (INT)" << endl;
		//float a = 2.5;
		//cout << (int)a << endl;//2
		//cout << a;

		//cout << (int)s7; // s1.operator int() { returns age && does not modify s7 }
		//or :cout << (double)s7;//return avg of grades

		cout << endl << "\nOperator []" << endl;
		cout << s7[0]; //s1.operator[](1)

		cout << endl << "\nOperator ! " << endl;
		/*if (!s1) {
			cout << "Student is not major";
		}
		else {
			cout << "Student is major";

		}*/

		//+=
		cout << s7;
		cout << s3;
		s7 += s3;  //s7.operator+=(s3) 
		cout << s7;

		s7 += 2;
		cout << s7;

		//+ 
		//s1 + s2
		cout << endl << "---------------";
		cout << s1;
		cout << s2;

		//Student s9 = s1 + s2;   //s1.operator+(s2)
		cout << endl << "s1+s2" << s1 + s2 << endl;
		cout << "s1+2" << s1 + 2 << endl;
		cout << "2+s1" << 2 + s1 << endl; //int.operator+(s1) // it worked initially because we have the int cast did previously 


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

