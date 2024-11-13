// stablo.h

#ifndef STABLO_H
#define STABLO_H

#include <vector>
#include <utility>
using namespace std;


class Stablo {
private:

    struct Cvor{
        int kljuc;
        int prioritet;
        Cvor* lijevo;
        Cvor* desno;
        Cvor* rod;
public:
        Cvor(int kljuc , int prioritet = -1) {
            this -> kljuc = kljuc;
            if ( prioritet < 0) this -> prioritet = rand()%100;
            else this -> prioritet = prioritet;
            this -> lijevo = nullptr;
            this -> desno = nullptr;
            this -> rod = nullptr;
        }
    };
    Cvor* korijen;

    Cvor* pretragaPrivate(int kljuc , Cvor* ptr);

    void ispisiSvePrivate( Cvor* ptr);

    void rotirajLijevo(Cvor* &ptr);
    void rotirajDesno(Cvor* &ptr);
    void InsertPrivate(int kljuc , Cvor* &ptr, bool = false);
    void ispisiPrivate( Cvor* ptr);
    int nadjiNajmanjegPrivate(Cvor*);
    int nadjiNajvecegPrivate(Cvor*);

    Cvor* ErasePrivate(int kljuc, Cvor * ptr);

public:

    Stablo();
    Stablo(Cvor* cvor);
    Cvor* getKorijen() const {
        return korijen;
    }
    void javnaRotacijaDesno(Cvor* ptr) {
        rotirajDesno(ptr);
    }
    void javnaRotacijaLijevo(Cvor* ptr) {
        rotirajLijevo(ptr);
    }
    Cvor* napraviCvor(int kljuc, int prioritet);
    Cvor* pretraga(int kljuc);
    void ispisiSve();
    void Insert(int kljuc , bool = false);
    void ispisi(); // ova funkcija se koristi za ispis kljuceva po velicini
    void Erase(int kljuc);

    nadjiNajmanjeg();
    nadjiNajveceg();


    friend Stablo Spajanje(Stablo stabloLijevo , Stablo stabloDesno);
};

pair<Stablo, Stablo> Razdvajanje(Stablo stablo, int k);


#endif // STABLO_H

