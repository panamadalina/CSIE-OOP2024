#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Base class representing a Component
class Component {
private:
    char* name;    // Name of the component
    float value;   // Value of the component

public:
    // Default constructor
    Component() {
        this->name = new char[strlen("N/A") + 1];
        strcpy(this->name, "N/A");
        this->value = 0;
    }

    // Parameterized constructor
    Component(const char* name, float value) {
        if (name != NULL) {
            this->name = new char[strlen(name) + 1];
            strcpy(this->name, name);
        } else {
            this->name = NULL;
        }
        this->value = value;
    }

    // Copy constructor
    Component(const Component& comp) {
        if (comp.name != NULL) {
            this->name = new char[strlen(comp.name) + 1];
            strcpy(this->name, comp.name);
        } else {
            this->name = NULL;
        }
        this->value = comp.value;
    }

    // Assignment operator
    Component& operator=(const Component& comp) {
        if (this->name != NULL) {
            delete[] this->name;
        }
        if (comp.name != NULL) {
            this->name = new char[strlen(comp.name) + 1];
            strcpy(this->name, comp.name);
        } else {
            this->name = NULL;
        }
        this->value = comp.value;
        return *this;
    }

    // Destructor
    ~Component() {
        if (this->name != NULL) {
            delete[] this->name;
        }
    }

    // Output operator for printing a component's details
    friend ostream& operator<<(ostream& out, const Component& comp) {
        out << "\nComponent " << comp.name << " has a value: " << comp.value;
        return out;
    }

    // Setters for name and value
    void setName(const char* newName) {
        if (newName != NULL) {
            if (this->name != NULL) {
                delete[] this->name;
            }
            this->name = new char[strlen(newName) + 1];
            strcpy(this->name, newName);
        }
    }

    void setValue(float newValue) {
        if (newValue > 0) {
            this->value = newValue;
        } else {
            throw "Invalid value!";
        }
    }

    float getValue() const {
        return this->value;
    }
};

// Class representing a Machine, containing multiple components
class Machine {
private:
    const int id;             // Unique ID of the machine
    int operationalTime;      // Operational time in hours
    Component* componentList; // List of components
    int numComponents;        // Number of components

public:
    // Default constructor
    Machine() : id(0) {
        this->operationalTime = 0;
        this->componentList = nullptr;
        this->numComponents = 0;
    }

    // Parameterized constructor
    Machine(int id, int operationalTime, Component* components, int numComponents) : id(id) {
        this->operationalTime = operationalTime;
        this->componentList = new Component[numComponents];
        for (int i = 0; i < numComponents; i++) {
            this->componentList[i] = components[i];
        }
        this->numComponents = numComponents;
    }

    // Copy constructor
    Machine(const Machine& machine) : id(machine.id) {
        this->operationalTime = machine.operationalTime;
        this->componentList = new Component[machine.numComponents];
        for (int i = 0; i < machine.numComponents; i++) {
            this->componentList[i] = machine.componentList[i];
        }
        this->numComponents = machine.numComponents;
    }

    // Assignment operator
    Machine& operator=(const Machine& machine) {
        if (this->componentList != NULL) {
            delete[] this->componentList;
        }
        this->operationalTime = machine.operationalTime;
        this->componentList = new Component[machine.numComponents];
        for (int i = 0; i < machine.numComponents; i++) {
            this->componentList[i] = machine.componentList[i];
        }
        this->numComponents = machine.numComponents;
        return *this;
    }

    // Destructor
    ~Machine() {
        if (this->componentList != NULL) {
            delete[] this->componentList;
        }
    }

    // Add a new component to the machine
    Machine operator+=(Component comp) {
        Component* tempList = new Component[this->numComponents];
        for (int i = 0; i < this->numComponents; i++) {
            tempList[i] = this->componentList[i];
        }
        delete[] this->componentList;

        this->componentList = new Component[this->numComponents + 1];
        for (int i = 0; i < this->numComponents; i++) {
            this->componentList[i] = tempList[i];
        }
        this->componentList[this->numComponents] = comp;
        this->numComponents++;
        delete[] tempList;
        return *this;
    }

    // Operator for casting to float (total value of all components)
    operator float() const {
        float totalValue = 0;
        for (int i = 0; i < this->numComponents; i++) {
            totalValue += this->componentList[i].getValue();
        }
        return totalValue;
    }

    // Access a specific component by index
    Component& operator[](int index) {
        if (index >= 0 && index < this->numComponents) {
            return this->componentList[index];
        } else {
            throw exception("Index out of range!");
        }
    }

    // Output operator for printing machine details
    friend ostream& operator<<(ostream& out, const Machine& machine) {
        out << "\nMachine ID: " << machine.id 
            << "\nNumber of Components: " << machine.numComponents 
            << "\nOperational Time: " << machine.operationalTime << " hours";
        for (int i = 0; i < machine.numComponents; i++) {
            out << machine.componentList[i];
        }
        return out;
    }
};

// Derived class representing a Replacement Component
class ReplacementComponent : public Component {
private:
    int replacementYear;

public:
    ReplacementComponent() : replacementYear(0) {}

    ReplacementComponent(const char* name, float value, int year) 
        : Component(name, value), replacementYear(year) {}
};

int main() {
    Component c1;
    Component c2("Component2", 20.4f);
    Component c3 = c2;
    c3.setName("Component3");
    try {
        c3.setValue(35.5f);
    } catch (const char* exp) {
        cout << exp;
    }

    cout << c3;

    Component components[3] = { c1, c2, c3 };
    Machine m1(12, 5, components, 3);

    Component c4("Component4", 12.0f);
    m1 += c4;

    cout << "\n\nMachine details:\n" << m1;
    cout << "\nTotal value of components: " << (float)m1 << endl;

    try {
        cout << m1[6];
    } catch (exception& ex) {
        cout << ex.what() << endl;
    }

    m1[0] = c4;
    cout << "\nMachine details after modification:\n" << m1;

    ReplacementComponent rc1("Replacement1", 10.0f, 2013);
    ReplacementComponent rc2("Replacement2", 50.0f, 2013);
    Component* compPtr = &rc1;
    cout << "\nValue of replacement component: " << compPtr->getValue() << endl;

    vector<Machine*> machines;
    Machine m2(12, 5, components, 2);

    machines.push_back(&m1);
    machines.push_back(&m2);

    cout << "\nMachines in vector:\n";
    for (auto it = machines.begin(); it != machines.end(); ++it) {
        cout << **it << endl;
    }

    return 0;
}
