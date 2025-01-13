#include<iostream>
using namespace std;

enum PerfumeType {
    MEN = 1,
    WOMEN = 2,
    CHILD = 3
};

class IOnlineSellable {
    virtual float getFinalPrice() = 0;
};

class Perfume : IOnlineSellable {
    char* brand;
    float price;
    bool isWrapped;
    static float wrappingCost;
    PerfumeType type;

public:
    Perfume() {
        this->brand = new char[strlen("unknown") + 1];
        strcpy(this->brand, "unknown");
        this->price = 0;
        this->isWrapped = false;
        this->type = PerfumeType::WOMEN;
    }

    Perfume(const char* brand, float price, bool isWrapped, PerfumeType type) {
        if (brand == NULL || strlen(brand) <= 2) {
            throw "\nInvalid brand name!\n";
        }
        this->brand = new char[strlen(brand) + 1];
        strcpy(this->brand, brand);
        this->price = price;
        this->isWrapped = isWrapped;
        this->type = type;
    }

    float getFinalPrice() {
        if (this->isWrapped) {
            return this->price + this->wrappingCost;
        }
        else {
            return this->price;
        }
    }

    ~Perfume() {
        if (this->brand) {
            delete[] this->brand;
        }
    }

    Perfume(const Perfume& p) {
        this->brand = new char[strlen(p.brand) + 1];
        strcpy(this->brand, p.brand);
        this->price = p.price;
        this->isWrapped = p.isWrapped;
        this->type = p.type;
    }

    Perfume& operator=(const Perfume& p) {
        if (this->brand) {
            delete[] this->brand;
        }
        this->brand = new char[strlen(p.brand) + 1];
        strcpy(this->brand, p.brand);
        this->price = p.price;
        this->isWrapped = p.isWrapped;
        this->type = p.type;
        return *this;
    }

    friend ostream& operator<<(ostream& out, Perfume p);

    bool operator>(Perfume& p) {
        return this->getFinalPrice() > p.getFinalPrice();
    }
};

float Perfume::wrappingCost = 50;

ostream& operator<<(ostream& out, Perfume p) {
    out << "\nThe perfume " << p.brand << " has shelf price: " << p.price << " and is for: ";
    if (p.type == PerfumeType::WOMEN) {
        out << " women";
    }
    if (p.type == PerfumeType::MEN) {
        out << " men";
    }
    if (p.type == PerfumeType::CHILD) {
        out << " children";
    }
    if (p.isWrapped) {
        out << " -> is wrapped";
    }
    else {
        out << " -> is NOT wrapped";
    }
    return out;
}

class ISortable {
    virtual void sort() = 0;
};

class IDisplayable {
    virtual void display() = 0;
};

class Collection : public ISortable, public IDisplayable {
    Perfume* perfumeList;
    int perfumeCount;

public:
    Collection(int perfumeCount, Perfume* perfumeList) {
        this->perfumeCount = perfumeCount;
        this->perfumeList = new Perfume[perfumeCount];
        for (int i = 0; i < perfumeCount; i++) {
            this->perfumeList[i] = perfumeList[i];
        }
    }

    void sort() {
        for (int i = 0; i < this->perfumeCount - 1; i++) {
            for (int j = i; j < this->perfumeCount; j++) {
                if (this->perfumeList[i] > this->perfumeList[j]) {
                    Perfume temp = this->perfumeList[i];
                    this->perfumeList[i] = this->perfumeList[j];
                    this->perfumeList[j] = temp;
                }
            }
        }
    }

    void display() {
        for (int i = 0; i < this->perfumeCount; i++) {
            cout << this->perfumeList[i];
        }
    }
};

int main() {
    try {
        Perfume p1("Dior", 200, true, PerfumeType::WOMEN);
        cout << p1;
        cout << "\n Final price: " << p1.getFinalPrice();

        Perfume p2("Chanel", 300, false, PerfumeType::MEN);
        Perfume p3("Zara", 100, true, PerfumeType::CHILD);

        Perfume* perfumeList = new Perfume[3];
        perfumeList[0] = p1;
        perfumeList[1] = p2;
        perfumeList[2] = p3;

        Collection collection(3, perfumeList);
        cout << endl;
        collection.display();
        collection.sort();
        cout << endl << endl << "After sorting:" << endl;
        collection.display();
    }
    catch (const char* excp) {
        cout << excp;
    }

    return 0;
}
