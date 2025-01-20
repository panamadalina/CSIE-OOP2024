#include <iostream>
#include <list>
#include <cstring>
using namespace std;

/* Polymorphism */
/*
1. Override -> late binding -> runtime
2. Overloading -> early binding -> compile time
*/

// Template function for generic addition
template<class Type>
Type sum(Type a, Type b) {
    return a + b; // Uses the "+" operator
}

// Enum for perfume types
enum PerfumeType {
    MAN = 1,    // Men's perfume
    WOMAN = 2,  // Women's perfume
    CHILD = 3   // Children's perfume
};

// Abstract interface for online sellable items
class IOnlineSellable {
    virtual float getFinalPrice() = 0;
};

// Class representing a perfume
class Perfume : IOnlineSellable {
    char* brand;                  // Name of the perfume brand
    float price;                  // Price of the perfume
    bool isPackaged;              // Whether the perfume is packaged
    static float packagingCost;   // Packaging cost (static for all perfumes)
    PerfumeType type;             // Type of perfume (man, woman, or child)

public:
    // Default constructor
    Perfume() {
        this->brand = new char[strlen("unknown") + 1];
        strcpy(this->brand, "unknown");
        this->price = 0;
        this->isPackaged = false;
        this->type = PerfumeType::WOMAN; // Default type: women's perfume
    }

    // Parameterized constructor
    Perfume(const char* brand, float price, bool isPackaged, PerfumeType type) {
        if (brand == NULL || strlen(brand) <= 2) {
            throw "\nInvalid brand name!\n";
        }
        this->brand = new char[strlen(brand) + 1];
        strcpy(this->brand, brand);
        this->price = price;
        this->isPackaged = isPackaged;
        this->type = type;
    }

    // Calculate the final price (including packaging cost if applicable)
    float getFinalPrice() {
        if (this->isPackaged) {
            return this->price + this->packagingCost;
        } else {
            return this->price;
        }
    }

    // Destructor to clean up dynamic memory
    ~Perfume() {
        if (this->brand) {
            delete[] this->brand;
        }
    }

    // Copy constructor
    Perfume(const Perfume& p) {
        this->brand = new char[strlen(p.brand) + 1];
        strcpy(this->brand, p.brand);
        this->price = p.price;
        this->isPackaged = p.isPackaged;
        this->type = p.type;
    }

    // Assignment operator
    Perfume& operator=(const Perfume& p) {
        if (this->brand) {
            delete[] this->brand;
        }
        this->brand = new char[strlen(p.brand) + 1];
        strcpy(this->brand, p.brand);
        this->price = p.price;
        this->isPackaged = p.isPackaged;
        this->type = p.type;
        return *this;
    }

    // Output operator for printing perfume details
    friend ostream& operator<<(ostream& out, Perfume p);

    // Comparison operator for perfumes based on final price
    bool operator>(Perfume& p) {
        return this->getFinalPrice() > p.getFinalPrice();
    }
};

// Static member initialization
float Perfume::packagingCost = 50;

ostream& operator<<(ostream& out, Perfume p) {
    out << "\nThe perfume " << p.brand << " has a shelf price of: " << p.price << " and is for: ";
    if (p.type == PerfumeType::WOMAN) {
        out << " women";
    } else if (p.type == PerfumeType::MAN) {
        out << " men";
    } else if (p.type == PerfumeType::CHILD) {
        out << " children";
    }
    if (p.isPackaged) {
        out << " -> it is packaged.";
    } else {
        out << " -> it is NOT packaged.";
    }
    return out;
}

// Template class for collections
template<class T>
class Collection {
    T* elements;      // Array of elements
    int numElements;  // Number of elements in the collection

public:
    // Default constructor
    Collection() {
        this->numElements = 0;
        this->elements = NULL;
    }

    // Parameterized constructor
    Collection(int numElements, T* elements) {
        this->numElements = numElements;
        this->elements = new T[numElements];
        for (int i = 0; i < numElements; i++) {
            this->elements[i] = elements[i];
        }
    }

    // Copy constructor
    Collection(const Collection& c) {
        this->numElements = c.numElements;
        if (c.elements != NULL) {
            this->elements = new T[c.numElements];
            for (int i = 0; i < c.numElements; i++) {
                this->elements[i] = c.elements[i];
            }
        } else {
            this->elements = NULL;
        }
    }

    // Destructor
    ~Collection() {
        if (this->elements != NULL) {
            delete[] this->elements;
        }
    }

    // Output operator for printing the collection
    friend ostream& operator<<(ostream& out, const Collection& c) {
        out << "\nThe collection has " << c.numElements << " elements: ";
        for (int i = 0; i < c.numElements; i++) {
            out << c.elements[i] << " ";
        }
        return out;
    }

    // Sorting method
    void sort() {
        for (int i = 0; i < numElements - 1; i++) {
            for (int j = i + 1; j < numElements; j++) {
                if (elements[i] > elements[j]) {
                    T temp = elements[i];
                    elements[i] = elements[j];
                    elements[j] = temp;
                }
            }
        }
    }
};

int main() {
    // Example of using the sum template function
    cout << sum(2, 3) << endl;
    cout << sum(2.5, 3.5) << endl;

    // Creating a collection of integers
    int* grades = new int[3]{10, 8, 9};
    Collection<int> gradeCollection(3, grades);
    cout << gradeCollection;

    // Creating and printing perfumes
    Perfume p1("Dior", 200, true, PerfumeType::MAN);
    Perfume p2("Chanel", 150, true, PerfumeType::WOMAN);
    Perfume* perfumeArray = new Perfume[2]{p1, p2};
    Collection<Perfume> perfumeCollection(2, perfumeArray);
    cout << "\n\n" << perfumeCollection;

    // Sorting and printing the collection
    perfumeCollection.sort();
    cout << "\nAfter sorting:\n" << perfumeCollection;

    return 0;
}
