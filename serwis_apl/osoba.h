#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <cstdio>

using namespace std;

class Osoba {
private:
	int id;
	string imie;
	string nazwisko;
	string data_p;
	string data_w;
	string sprzet;
	string status;
	string usluga_k;
	string opis;
public:
	int ID() const;
	string Imie() const;
	string Nazwisko() const;
	string Data_pget() const;
	string Data_wget() const;
	string Sprzet() const;
	string Status() const;
	string Usluga_k() const;
	string Opis() const;

	void ID(int nid);
	void Imie(string nimie);
	void Nazwisko(string nnazwisko);
	void Data_pset();
	void Data_wset();
	void Data_wset(string ndata_w);
	void Sprzet(string nsprzet);
	void Status(string nstatus);
	void Usluga_k(string nusluga_k);
	void Opis(string nopis);
};
