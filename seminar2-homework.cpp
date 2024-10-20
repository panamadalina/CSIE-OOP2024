#include <iostream>
using namespace std;

// Funcția recursivă oglindit
int oglindit(int x, int ogl = 0) {
    // Condiția de oprire: dacă x a devenit 0, returnăm oglinditul complet
    if (x == 0) 
        return ogl;
    
    // Actualizăm oglinditul prin adăugarea ultimei cifre a lui x la ogl și continuăm recursiv
    return oglindit(x / 10, ogl * 10 + x % 10);
}

int main() {
    int x;
    cout << "Introduceti un numar: ";
    cin >> x;
    
    // Apelăm funcția oglindit din main și afișăm rezultatul
    cout << "Numarul oglindit este: " << oglindit(x) << endl;
    
    return 0;
}
