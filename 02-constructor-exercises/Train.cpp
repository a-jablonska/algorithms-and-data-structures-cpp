#include <iostream> 
using namespace std;

struct Carriage {
    int passengers;
    Carriage* next; //pointer to the next carriage (nullptr = last one)

    Carriage(int p, Carriage* n=nullptr) {
        passengers = p; // p = number of passengers
        next = n;
    }
};

int main() {
    Carriage* Carriage2 = new Carriage(25);
    Carriage* Carriage1 = new Carriage(40, Carriage2);
    Carriage* Locomotive = new Carriage(0, Carriage1);

    int sum = 0;
    Carriage* c = Locomotive; // c moving through carriages
    while(c != nullptr) {
        sum += c->passengers;
        c = c->next;
    }

    Carriage* k = Locomotive;
    for (int i = 0; i < 2; i++) { // walk 2 steps from the locomotive to the last carriage
        k = k->next;
    }


    cout << Locomotive->passengers << endl; //shows amount of passengers in locomotive
    cout << Locomotive->next->passengers << endl; //shows amount of passengers in next carriage after locomotive
    cout << Locomotive->next->next->passengers << endl; //shows amount of passengers in next next carriage after locomotive
    cout << k->passengers << endl;
    cout << "Passengers sum in train: " << sum << endl;

    delete Locomotive;
    delete Carriage1;
    delete Carriage2;

    return 0;
}