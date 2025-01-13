#include<iostream>
using namespace std;

class A {
public:
    int x() {
        return 0;
    }
};

class B {
public:
    int x() {
        return 2;
    }
    int y() {
        return 1;
    }
};

class C : public A, public B {

};

class Person {
public:
    // name
    // age
    int x;
};

class Student : public Person {
    // university
    // scholarship
};

class Employee : public Person {
    // salary
    // company
};

class Elder : public Employee, public Student {
    // pension
};

/*-------------------------------------------------*/
class Worker {
public:
    int salary;
    Worker() {
        salary = 0;
    }
};

class Manager : virtual public Worker {
    // subordinates
public:
    Manager() {
        salary = 100;
    }
};

class Professor : virtual public Worker {
    // students
public:
    Professor() {
        salary = 50;
    }
};

class Individual : public Manager, public Professor {
    // bonus for hard work
};

// Polymorphism
/*
1.override -> late biding -> executie

2. overloading -> early binding -> compilarii
*/
class Bird {
public:
    virtual void fly2() = 0; // At least one pure virtual function makes Bird an abstract class
    virtual void fly() { // Virtual function
        cout << " \n-> flies";
    }
};

class Eagle : public Bird {
    void fly2() {
        // Do something specific to Eagle
    }
};

class Penguin : public Bird {
public:
    void fly2() {
        // Do something specific to Penguin
    }
    void fly() {
        cout << " \n-> does not fly";
    }
};

int main() {
    C cInstance;
    cout << cInstance.B::x(); // Ambiguity problem -> multiple inheritance
    // cout <<endl<< cInstance.y();
    A aInstance;
    /*aInstance.C::x();*/

    // Upcasting
    // Elder -> Employee
    Employee emp;
    // Elder elder;
    // emp = elder; // Information is lost

    Person person;
    // person = elder; // Does not work -> upcasting across multiple levels

    // Stepwise upcasting
    // person = emp; // person=elder || emp=elder -> person=emp

    // Downcasting does not work in this case:
    // int = 2 -> float = 2.00 

    // Diamond inheritance problem
    cout << endl << endl;
    Individual individual;
    cout << individual.Professor::salary << endl;
    cout << individual.Manager::salary;
    // Virtual inheritance -> unique salary
    Worker worker;
    worker = individual; // Direct upcasting -> virtual inheritance

    // Polymorphism
    // 1. Overloading -> functions -> int sum(int a, int b) -> int sum(int a, float b)
    // sum(2, 3) and sum(2, 3.4)

    // 2. Overriding -> classes
    Eagle eagle;
    cout << "Eagle:";
    eagle.fly();

    Penguin penguin;
    cout << "\n Penguin:";
    penguin.fly();

    cout << endl;
    Bird* bird = new Penguin();
    // Bird bird; -> does not work
    // Class Bird has a virtual function
    // => Bird is an abstract class
    // -> cannot instantiate an object
    // -> can only use a pointer!

    cout << "\n Penguin2:";
    bird->fly();

    cout << endl << endl;

    return 0;
}
