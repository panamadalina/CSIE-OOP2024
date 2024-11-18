#include<iostream>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS

struct Pers {
    //private:	
    int cnp;
    char* nume;
};

class Persoana {//user defined type of data private:
    int cnp;
    char* name;
public:
    int something = 0;

    //default constructor:
    Persoana() {
        //name = "N/A";
        std::cout << endl << "Default constr was called..." << endl;
    }
    const char* getName(int password) {
        if (password == 1234) {
            return name;
        }
        else {
            return "\nSorry";
        }
    }
    const char* setName(int password, const char* newName) {
        if (password == 1234) {
            if (name == NULL) {//strlen //nullptr
                //1.delete
                delete[] name;
                name = nullptr;
            }
            //2.create new space
            name = new char[strlen(newName) + 1];
            //3.copy the value 
            strcpy(name, newName) ;
            //usually no return
            return "\nName has been modified";
        }
        else {
            return "\nnot authorized";
        }
    }
    //protected:
    //polymorphism (type: overloading)
    double sum(double a, double b);
    int sun(int a, int b) {
        return a * b;
    }
    //int sum(double a, int b) { return a * b};

};
double Persoana::sum(double a, double b) {
    return a + b;
}
int main() {
    Pers p;
	p.cnp = 1234;

    Persoana p1;
    p1.something = 2;
    std::cout << p1.something;
    //acces methods: getters & setters cout<<pl.getName (2345) ;
    cout << p1.setName(1234, "Madalina"); 
    cout << endl << p1.getName(1234);

    //Persoana:: static Functions 
    cout << endl << p1.sum(2, 3);//convert int-›double l adding info C.0) 
    cout<< endl << p1.sum(2.5, 3.5); //convert from double to int 
    //remove info that does not need (.5)

    cout<< endl << "P2:";
    Persoana* p2;
    p2 = &p1;//p2 is pointer to object p1
    cout << p2->getName(1234);
    
    return 0;
}