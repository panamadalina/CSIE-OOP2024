#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
// #include <crtdbg.h>

using namespace std;
//int globaltotal = 0;
void oglinditSem1(int nr, int x) {
    
    while (nr) {
        x = x * 10 + nr % 10;
        nr /= 10;
    }
    if (x != 0) {
        cout << "\nDin functie1:" << x;
    }

}

void oglinditSem2(int nr, int* x) {

    while (nr) {
        (*x) = (*x) * 10 + nr % 10;
        nr /= 10;
    }
    if ((*x) != 0) {
        cout << "\nDin functie2:" << x;
    }

}

int main() 
{
    int nr = 1234;
    int nrOglindit = 0;
 /*   cout << "\nnrOglindit:" << nrOglindit;*/
    oglinditSem1(nr, nrOglindit);
    cout << "\nDin main1:" << nrOglindit;
    cout << "\nnrOglindit:" << &nrOglindit;

    //int * float*
    //cout <<"\nchar*="<< sizeof(char*);
    oglinditSem2(nr, &nrOglindit);
    cout << "\nDin main2:" << nrOglindit;

    //NEW vs MALLOC
    //v* 4 bytes
    //v[] 20 bytes
    int* v = new int[5];
   
    v[0] = 10;
    v[1] = 20;
    v[2] = 10;
    v[3] = 20;
    v[4] = 10;
  
   // v[5] = 20;
    cout << "\nv[0]=" << v[0];

    delete[] v;

    float* vect = (float*)malloc(sizeof(float));
    vect[6] = 20;
    cout << "\nvect[6]=" << vect[6];
    free(vect);


    // _CrtDumpMemoryLeaks();
    return 0;
}
//CRT library:
/*https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019*/