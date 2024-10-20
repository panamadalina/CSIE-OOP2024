#include<iostream>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

//enumeratie - tip de data ce rastrange numarul de valori posibile
//la cele de mai jos
enum ziSaptamana { luni = 1, marti = 2, miercuri = 3,joi=4,vineri=5};


struct Student {
	char* nume;//4B
	int varsta;//4B
	bool lucreaza;//1B
};

void main() {
	/*Exemplu 1:*/

	//cout << ziSaptamana::luni;
	ziSaptamana zi = ziSaptamana::vineri;

	cout << "\nzi:" << zi;
	zi = (ziSaptamana)1;

	/*------------------------------------------------------------*/
	/*Exemplu 2*/

	//Operatiile aritmetice permise asupra pointerilor sunt:
	//adunarea / scaderea unei constante, 
	//incrementarea / decrementarea si 
	//scaderea a doi pointeri de acelasi tip.

	int x = 10;
	int* pointer = &x;
	//A) creste adresa salvata in pointer cu sizeof(int)
	cout << "\nAdresa pointer1=" << pointer << endl;
	pointer++;
	cout << "\nAdresa pointer2=" << pointer << endl;

	//B) q salveaza o adresa mai mica cu 2 * sizeof(int) decat pointer
	int* qpointer = pointer - 2;
	cout << "\nAdresa pointer3=" << qpointer << endl;

	//C) Adunare 2 pointeri -> INTERZIS
	//cout << pointer + qpointer;//Nu merge!!
	
	//D) diferenta a doi pointeri este un intreg
	//si reprezinta cate variabile de tip int, in acest caz particular
	//incap intre cele doua adrese de memorie
	printf("%dScadere dintre 2 pointeri=\n", pointer - qpointer);

	/*---------------------------------------------------------*/
	/*Exemplu 3:*/

	//Adunarea cu 1, face ca un pointer sa indice urmatorul obiect de acelasi tip iar
	//decrementarea face ca el sa indice obiectul imediat anterior in spatiul de memorie.

	
	int* v = new int[3];
	v[0] = 0; v[1] = 1; v[2] = 2;
	cout << "\nv=" << v;
	cout <<"\n*v+1 = "<< * v + 1;//NU e bine! e o coincidenta!


	v[0] = 1; v[1] = 3; v[2] = 5;
	//cout << *(v + 1);
	cout <<"\n*(1+v) = "<< * (1 + v);
	//cout << endl << "\n*(v+1)=v[1]";
	
	delete[]v;
	/*-------------------------------------------------------------*/
	

	_CrtDumpMemoryLeaks();
}