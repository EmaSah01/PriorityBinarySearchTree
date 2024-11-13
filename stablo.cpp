// stablo.cpp

#include <iostream>
#include "stablo.h"

using namespace std;

Stablo::Stablo()
{
    korijen = nullptr;
}

Stablo::Stablo(Cvor *cvor)
{
    korijen = cvor;
}

Stablo::Cvor* Stablo::pretraga(int kljuc) {
    return pretragaPrivate(kljuc, korijen);
}

Stablo::Cvor* Stablo::pretragaPrivate(int kljuc, Cvor* ptr) {
    if (ptr == nullptr) {
        return nullptr;
    } else if (ptr->kljuc == kljuc) {
        return ptr;
    } else if (kljuc < ptr->kljuc) {
        return pretragaPrivate(kljuc, ptr->lijevo);
    } else {
        return pretragaPrivate(kljuc, ptr->desno);
    }
}


void Stablo::ispisiSve() {
    ispisiSvePrivate(korijen);
}

void Stablo::ispisiSvePrivate(Cvor* ptr) {
    if (ptr != nullptr) {
        cout << "K: " << ptr->kljuc << ", P: " << ptr->prioritet;

        if (ptr->lijevo != nullptr) {
            cout << ", Lijevo dijete: K " << ptr->lijevo->kljuc << " P " << ptr->lijevo-> prioritet;
        }

        if (ptr->desno != nullptr) {
            cout << ", Desno dijete: K " << ptr->desno->kljuc<< " P " << ptr-> desno -> prioritet;;
        }
        cout << endl;

        ispisiSvePrivate(ptr->lijevo);
        ispisiSvePrivate(ptr->desno);
    }
}

void Stablo::Insert(int kljuc, bool uslov) {
    cout << "Dodajem kljuc " << kljuc << " u stablo." << endl;
    InsertPrivate(kljuc, korijen,uslov);
}

void Stablo::rotirajLijevo(Cvor* &ptr) {
   Cvor* DesnoDijete = ptr->desno;
   Cvor* LijevoDijeteDesnogDjeteta = ptr->desno->lijevo;
   DesnoDijete->lijevo = ptr;
   ptr->desno= LijevoDijeteDesnogDjeteta;
   ptr = DesnoDijete;
}


void Stablo::rotirajDesno(Cvor* &ptr) {
   Cvor* LijevoDijete = ptr->lijevo;
   Cvor* DesnodijeteLijevogDjeteta = ptr->lijevo->desno;
   LijevoDijete->desno = ptr;
   ptr->lijevo= DesnodijeteLijevogDjeteta;
   ptr = LijevoDijete;
}


void Stablo::InsertPrivate(int kljuc, Cvor* &ptr , bool uslov) {
    if (ptr == nullptr) {
        // dodajem korijen s kljucem
        if(!uslov) ptr = new Cvor(kljuc);
        else ptr = new Cvor(kljuc, (this -> korijen -> prioritet) + 1);

        return;
    }

    if (kljuc < ptr->kljuc) {
        InsertPrivate(kljuc, ptr->lijevo , uslov);
        if (ptr->lijevo != nullptr && ptr -> lijevo -> prioritet > ptr -> prioritet){
                rotirajDesno(ptr);
            }
        }
     else if (kljuc > ptr->kljuc) {
        InsertPrivate(kljuc, ptr->desno, uslov);
        if (ptr->desno != nullptr && ptr -> desno -> prioritet > ptr -> prioritet){
                rotirajLijevo(ptr);
            }
        }
     else {
        cout << "Kljuc " << kljuc << " je vec dodan u stablo\n";
    }
}

void Stablo::ispisi() {
    ispisiPrivate(korijen);
}

void Stablo::ispisiPrivate(Cvor* ptr)
{
    if (korijen != NULL) {
        if( ptr -> lijevo != NULL)
        {
            ispisiPrivate(ptr -> lijevo);
        }
        cout << "Kljuc: " <<ptr -> kljuc << "  Prioritet: " << ptr -> prioritet<< "\n";
        if( ptr -> desno != NULL)
        {
            ispisiPrivate( ptr -> desno);
        }
    }
    else {
        cout << "Stablo je prazno\n! " << endl;
    }
}

void Stablo::Erase(int kljuc) {
    if (pretraga(kljuc)) {
        korijen = ErasePrivate(kljuc, korijen);
        cout << "Cvor s kljucem " << kljuc << " uspjesno izbrisan." << endl;
    } else {
        cout << "Cvor s kljucem " << kljuc << " nije pronadjen u stablu." << endl;
    }
}

Stablo::Cvor* Stablo::ErasePrivate(int kljuc, Cvor* korijen) {
    if (korijen == nullptr) {
        return nullptr;
    }
    if (kljuc < korijen->kljuc) {
        korijen->lijevo = ErasePrivate(kljuc, korijen->lijevo);
    } else if (kljuc > korijen->kljuc) {
        korijen->desno = ErasePrivate(kljuc, korijen->desno);
    } else {
        // Pronađen čvor koji se želi obrisati

        // Ako čvor nema lijevo dijete ili desno dijete
        if (korijen->lijevo == nullptr) {
            Cvor* temp = korijen->desno;
            delete korijen;
            return temp;
        } else if (korijen->desno == nullptr) {
            Cvor* temp = korijen->lijevo;
            delete korijen;
            return temp;
        }

        // Ako čvor ima oba djeteta
        if (korijen->lijevo->prioritet < korijen->desno->prioritet) {
            rotirajLijevo(korijen);
            korijen->lijevo = ErasePrivate(kljuc, korijen->lijevo);
        } else {
            rotirajDesno(korijen);
            korijen->desno = ErasePrivate(kljuc, korijen->desno);
        }
    }

    return korijen;
}


pair<Stablo,Stablo> Razdvajanje(Stablo stablo , int kljuc) {

    stablo.Insert(kljuc, true);


    stablo.ispisiSve();

    Stablo stabloLijevo(stablo.pretraga(kljuc) -> lijevo);
    Stablo stabloDesno(stablo.pretraga(kljuc) -> desno);


    return {stabloLijevo , stabloDesno};

}

int Stablo::nadjiNajmanjegPrivate(Cvor* ptr) {
    if (ptr == nullptr) {
        return INT_MAX;
    }
    while (ptr->lijevo != nullptr) {
        ptr = ptr->lijevo;
    }
    return ptr->kljuc;
}

int Stablo::nadjiNajmanjeg() {
    return nadjiNajmanjegPrivate(korijen);
}

int Stablo::nadjiNajvecegPrivate(Cvor* ptr) {
    if (ptr == nullptr) {
        return INT_MIN;
    }
    while (ptr->desno != nullptr) {
        ptr = ptr->desno;
    }
    return ptr->kljuc;
}

int Stablo::nadjiNajveceg() {
    return nadjiNajvecegPrivate(korijen);
}


Stablo Spajanje(Stablo stabloLijevo, Stablo stabloDesno)
{
    int najveci_lijevo = stabloLijevo.nadjiNajveceg();

    int najmanji_desno = stabloDesno.nadjiNajmanjeg();

    int novi_kljuc = (najveci_lijevo + najmanji_desno) / 2;


    Stablo stablo;
    stablo.Insert(novi_kljuc, true);

    stablo.getKorijen()->lijevo = stabloLijevo.getKorijen();
    stablo.getKorijen()->desno = stabloDesno.getKorijen();

    while (stablo.getKorijen()->lijevo != nullptr || stablo.getKorijen()->desno != nullptr) {
        if (stablo.getKorijen()->lijevo != nullptr && stablo.getKorijen()->lijevo->prioritet > stablo.getKorijen()->prioritet) {
            stablo.javnaRotacijaDesno(stablo.getKorijen());
        } else if (stablo.getKorijen()->desno != nullptr && stablo.getKorijen()->desno->prioritet > stablo.getKorijen()->prioritet) {
            stablo.javnaRotacijaLijevo(stablo.getKorijen());
        } else {
            break;
        }
    }

    stablo.ispisiSve();

    return stablo;
}






