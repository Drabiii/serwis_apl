#include "osoba.h"
using namespace std;
string Korygujdate();

#pragma region Get

int Osoba::ID() const {
    return id;
};
string Osoba::Imie() const {
    return imie;
};
string Osoba::Nazwisko() const {
    return nazwisko;
};
string Osoba::Data_pget() const {
    return data_p;
};
string Osoba::Data_wget() const {
    return data_w;
};
string Osoba::Sprzet() const {
    return sprzet;
};
string Osoba::Status() const {
    return status;
};
string Osoba::Usluga_k() const {
    return usluga_k;
};
string Osoba::Opis() const {
    return opis;
};
#pragma endregion

#pragma region Set

void Osoba::ID(int nid) {
    id = nid;
};
void Osoba::Imie(string nimie) {
    imie = nimie;
};
void Osoba::Nazwisko(string nnazwisko) {
    nazwisko = nnazwisko;
};
void Osoba::Data_pset() {
    string temp;
    char c;
    time_t rawtime;
    tm* timeinfo;
    char bufferdzien[5];
    char buffermies[10];
    char bufferrok[5];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(bufferdzien, 5, "%d", timeinfo);
    strftime(buffermies, 10, "%m", timeinfo);
    strftime(bufferrok, 5, "%Y", timeinfo);
    cout << "Dzisiejsza data to : " << bufferdzien << "-" << buffermies << "-" << bufferrok << endl;
    cout << "Czy chcesz zmienic date przyjecia? t/n" << endl;
    do {
        cout << ">> ";
        cin >> c;
        if (c == 't' || c == 'T') {
            data_p = Korygujdate();
            break;
        } else if (c == 'n' || c == 'N') {
            temp = bufferdzien;
            data_p += temp;
            data_p += "-";
            temp = buffermies;
            data_p += temp;
            data_p += "-";
            temp = bufferrok;
            data_p += temp;
            break;
        } else {

        }
    } while (c != 't' || c != 'T' || c != 'n' || c != 'N');
};
void Osoba::Data_wset() {
    string temp;
    char c;
    time_t rawtime;
    tm* timeinfo;
    char bufferdzien[5];
    char buffermies[10];
    char bufferrok[5];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(bufferdzien, 5, "%d", timeinfo);
    strftime(buffermies, 10, "%m", timeinfo);
    strftime(bufferrok, 5, "%Y", timeinfo);
    cout << "Dzisiejsza data to : " << bufferdzien << "-" << buffermies << "-" << bufferrok << endl;
    cout << "Czy chcesz zmienic date wydania t/n" << endl;
    do {
        cout << ">> ";
        cin >> c;
        if (c == 't' || c == 'T') {
            data_p = Korygujdate();
            break;
        }
        else if (c == 'n' || c == 'N') {
            temp = bufferdzien;
            data_p += temp;
            data_p += "-";
            temp = buffermies;
            data_p += temp;
            data_p += "-";
            temp = bufferrok;
            data_p += temp;
            break;
        }
        else {

        }
    } while (c != 't' || c != 'T' || c != 'n' || c != 'N');
};
void Osoba::Data_wset(string ndata_w) {
    data_w = ndata_w;
};
void Osoba::Sprzet(string nsprzet) {
    sprzet = nsprzet;
};
void Osoba::Status(string nstatus) {
    status = nstatus;
};
void Osoba::Usluga_k(string nusluga_k) {
    usluga_k = nusluga_k;
};
void Osoba::Opis(string nopis) {
    opis = nopis;
};
#pragma endregion

#pragma region Funkcja_Koryguj_Date

string Korygujdate() {
wprowadz:
    int dzien;
    int mies;
    int rok;
    cout << "Podaj dzien: ";
    cin >> dzien;
    cout << "Podaj Miesiac: ";
    cin >> mies;
    cout << "Podaj Rok: ";
    cin >> rok;

    string bufferdzien;
    string buffermies;
    string bufferrok;
    string data;

    if (dzien < 0) {
        dzien = 1;
    } else if (dzien > 31) {
        dzien = 31;
    } else {

    }
    if (rok >= 1000 && rok <= 3000) {
        if (mies < 1) {
            mies = 1;
        } else if (mies > 12) {
            mies = 12;
        } else

        if ((mies == 1 || mies == 3 || mies == 5 || mies == 7 || mies == 8 || mies == 10 || mies == 12) && dzien > 0 && dzien <= 31) {
            bufferdzien = to_string(dzien);
            buffermies = to_string(mies);
            bufferrok = to_string(rok);
        } else {
            if ((mies == 4 || mies == 6 || mies == 9 || mies == 11) && dzien > 0 && dzien <= 30) {
                bufferdzien = to_string(dzien);
                buffermies = to_string(mies);
                bufferrok = to_string(rok);
            } else {
                if (mies == 2) {
                    if ((rok % 400 == 0 || (rok % 100 != 0 && rok % 4 == 0)) && dzien > 0 && dzien <= 29) {
                        bufferdzien = to_string(dzien);
                        buffermies = to_string(mies);
                        bufferrok = to_string(rok);

                    } else if (dzien > 0 && dzien <= 28) {
                        bufferdzien = to_string(dzien);
                        buffermies = to_string(mies);
                        bufferrok = to_string(rok);
                    } else {
                        cout << "Wprowadzono NIE poprawna date!" << "\n" << "Wpisz date jeszcze raz!" << endl << "->";
                        goto wprowadz;
                    }
                } else {
                    cout << "Wprowadzono NIE poprawna date!" << "\n" << "Wpisz date jeszcze raz!" << endl << "->";
                    goto wprowadz;
                }
            }
        }
    } else {
        cout << "Wprowadzono NIE poprawna date!" << "\n" << "Wpisz date jeszcze raz!" << endl << "->";
        goto wprowadz;
    }
    data = bufferdzien;
    data += "-";
    data += buffermies;
    data += "-";
    data += bufferrok;

    return data;
}
#pragma endregion



