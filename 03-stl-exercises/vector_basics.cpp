//Zadanie 1: konstruktor vectora. Utwórz vector<int> v(5, 7); i wypisz wszystkie elementy pętlą. Potem zmień v[2] na 100, wypisz jeszcze raz i wypisz v.size().
//Oczekiwany wynik: 7 7 7 7 7, potem 7 7 100 7 7, potem 5.

#include <iostream>
#include <vector>
using namespace std;

vector<int> v(5,7); // tablica dynamiczna - moze rosnac w trakcie programu; 5 x 7; v[7, 7, 7, 7, 7]
vector<int> x;
vector<int> z(8, 0); 

int main() {
    v[2]=123; //zamieniamy element o 2 indeksie

    x.push_back(7); //push back dodaje element na koniec tablicy
    x.push_back(7);
    x.push_back(100);
    x.push_back(7);
    x.push_back(7);
    x.push_back(5);

    for (int i=0; i < (int)v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Rozmiar tablicy v: " << v.size();
    cout << endl;

    for (int i = 0; i < (int)x.size(); i++){
        cout << x[i] << " ";
    }
    cout << endl;
    cout << "Rozmiar tablicy x: " << x.size();
    cout<<endl;

    return 0;
}