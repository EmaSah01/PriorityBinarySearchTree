
// main.cpp


#include <iostream>
#include <vector>
#include <utility>
#include "stablo.h"

using namespace std;

int main() {

    vector<int> kljuceviStabla = {24, 6 , 47 , 2 , 16, 32};

    Stablo stablo;

    for( int i = 0 ; i < kljuceviStabla.size() ; i++)
    {
        stablo.Insert(kljuceviStabla[i]);
    }

    cout << endl;
    if (stablo.pretraga(52) != nullptr) cout << "Cvor se nalazi u stablu" << endl;
    if (stablo.pretraga(16) != nullptr) cout << "Cvor se nalazi u stablu" << endl;

    cout << endl;
    stablo.ispisiSve();

    //stablo.izbrisiCvor(86);
    //stablo.izbrisiCvor(16);
    stablo.Erase(24);
    cout << endl;
    stablo.ispisiSve();

    cout << endl;

    pair<Stablo, Stablo> stabla;

    stabla = Razdvajanje(stablo, 17);
    cout << endl;
    stabla.second.ispisiSve();
    cout << endl;
    stabla.first.ispisiSve();

    cout << endl;


    //Stablo rezultat = Spajanje(stabla.first , stabla.second);

    //rezultat.ispisiSve();

    return 0;
}
