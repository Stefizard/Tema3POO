#include <iostream>
#include <string>

#include "include/HashTable.h"

/// Tema 3 POO - Ifrimenco Alexandru - Daniel

/// HashTable
using namespace std;

int main()
{
    cout << "###### Tema 3 POO - Ifrimenco Alexandru - Daniel\n\n\n\n@@@@@@     Program demonstrativ     @@@@@@\n\n\n";
    HashTable<int, int> A;
    int x =3, y = 2, z;
    A.AddValue(x, 28);
    A.AddValue(y, 3);
    cout << A;
    HashTable<int, int> B(A);
    cout << B.GetDistinctKeys() << "\n";
    B.DeleteValues(x);
    B[y] = 7;
    cout << B;
    cout << B.GetDistinctKeys() << "\n";
    B.AddValue(x, 3);
    B.AddValue(x, 4);
    B.AddValue(x, 2);
    vector <int> sol;
    sol = B.GetAllValues(x);
    for (vector <int> :: iterator it = sol.begin(); it != sol.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
    cout << B.Search(x, 2) << "\n";
    cout << B.Search(x, 100) << "\n";
    A = B;
    cout << A;
    return 0;
}
