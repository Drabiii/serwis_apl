#include "funkcje.h"
#include <mysql.h>
#include <limits> 
#undef max

#pragma region CzyszczenieBuforu

void CzyszczenieBuff() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
};

#pragma endregion

#pragma region PolaczenieMySQL

MYSQL* Conn(MYSQL* conn) {
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "1234", "osoby", 3306, NULL, 0);
	if (*mysql_error(conn)) {
		cout << "Blad: >> " << *mysql_error(conn) << endl;
	}
	else {
		cout << "---Poprawnie polaczono z baza danych!---" << endl;
	}
	return conn;
};

#pragma endregion

#pragma region ZapytanieDoBazyMySQL

bool ZapytanieDoBazy(string query) {
	MYSQL* conn = mysql_init(0);
	int qstate;

	conn = Conn(conn);
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (qstate) {
		cout << "Blad! >> " << mysql_error(conn);
		system("pause");
		mysql_close(conn);
		return 0;
	}
	else {
		mysql_close(conn);
		return 1;
	}
};

#pragma endregion

#pragma region Conn_wypisywanieMySQL

void Connwyp(string query) {
	system("cls");
	MYSQL* conn = mysql_init(0);
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = Conn(conn);
	int qstate;
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (qstate) {
		cout << "Nie mozna wypisac!: " << mysql_error(conn) << endl;
		system("pause");
	}
	else {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			cout << endl << "ID{" << row[0] << "} | Imie i Nazwisko: " << row[1] << " " << row[2] << " | Data przyjecia: "
				<< row[3] << " | Data Wydania: " << row[4] << " | Sprzet: " << row[5] << " | Status: " << row[6]
				<< " | Koszt uslugi: " << row[7] << " zl" << endl << "Opis: " << row[8] << endl;
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	mysql_close(conn);
};

#pragma endregion

#pragma region PrzenosenieMySQL

bool Przenies(int id) {
	system("cls");
	MYSQL* conn = mysql_init(0);
	MYSQL_ROW row;
	MYSQL_RES* res;
	const char* q;
	string query;
	string otrzymaneID;
	string imie;
	string nazwisko;
	string data_p;
	string data_w;
	string sprzet;
	string status;
	string koszt_u;
	string opis;


	conn = Conn(conn);
	query = "SELECT * FROM aktywne WHERE id=" + to_string(id);
	int qstate;
	q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			otrzymaneID = row[0];
			imie = row[1];
			nazwisko = row[2];
			data_p = row[3];
			data_w = row[4];
			sprzet = row[5];
			status = row[6];
			koszt_u = row[7];
			opis = row[8];
		}
		query = "INSERT INTO zakonczone(id,imie,nazwisko,data_p,data_w,sprzet,status,usluga_k,opis) VALUES (\"" +
			otrzymaneID + "\", \"" +
			imie + "\", \"" +
			nazwisko + "\", \"" +
			data_p + "\", \"" +
			data_w + "\", \"" +
			sprzet + "\", \"" +
			status + "\", \"" +
			koszt_u + "\", \"" +
			opis + "\")";
		q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			query = "DELETE FROM aktywne WHERE id=" + to_string(id);
			q = query.c_str();
			qstate = mysql_query(conn, q);
			if (qstate) {
				cout << "Blad! >> " << mysql_error(conn) << endl;
				system("pause");
				mysql_close(conn);
			}
			else {
				cout << "Poprawnie przeniesiono wpis!" << endl;
				system("pause");
			}
		}
		else {
			cout << "Blad! >> " << mysql_error(conn) << endl;
			system("pause");
			mysql_close(conn);
		}

	}
	else {
		cout << "Nie mozna wypisac!: " << mysql_error(conn) << endl;
		system("pause");
		mysql_close(conn);
	}
};

#pragma endregion

#pragma region Pobieranie daty

string PobierzDateWydania(string query) {
	MYSQL* conn = mysql_init(0);
	MYSQL_ROW row;
	MYSQL_RES* res;
	string ndata_w;

	conn = Conn(conn);
	int qstate;
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (qstate) {
		cout << "Nie mozna odczytac!: " << mysql_error(conn) << endl;
		system("pause");
	}
	else {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			ndata_w = row[0];
		}
		return ndata_w;
	}
	mysql_close(conn);
};

#pragma endregion

#pragma region Conn_Sprawdzanie_IDMySQL

bool Connsprid(string query) {
	string spr;
	MYSQL* conn = mysql_init(0);
	MYSQL_ROW row;
	MYSQL_RES* res;

	conn = Conn(conn);

	int qstate;
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			spr = row[0];
		}
		if (spr == "1") {
			cout << "ID Poprawne!" << endl;
			mysql_close(conn);
			return 1;
		}
		else {
			cout << "Takie ID nie wystepuje w bazie!" << endl;
			mysql_close(conn);
			return 0;
		}
	}
	else {
		cout << "Takie ID nie wystepuje w bazie!" << endl;
		mysql_close(conn);
		return 0;
	}
};

#pragma endregion



#pragma region Funkcja_Dodaj

void Dodaj() {
	system("cls");
	int wyb;
	Osoba osoba;
	string nimie;
	string nnazwisko;
	string ndata_p;
	string ndata_w;
	string nsprzet;
	string nstatus;
	string nusluga_k;
	string nopis;

	cout << "Podaj imie: ";
	cin >> nimie;
	osoba.Imie(nimie);
	cout << "Podaj nazwisko: ";
	cin >> nnazwisko;
	osoba.Nazwisko(nnazwisko);
	osoba.Data_pset();
wyb:
	wyb = 0;
	cout << "Jakie urzadzenie przyniosl klient?" << endl;
	cout << "1. Laptop" << endl;
	cout << "2. Komputer" << endl;
	cout << "3. Konsola" << endl;
	cout << "4. Inne urzadzenie" << endl;
	cin >> wyb;
	switch (wyb) {
	case 1:
		osoba.Sprzet("Laptop");
		break;
	case 2:
		osoba.Sprzet("Komputer");
		break;
	case 3:
		osoba.Sprzet("Konsola");
		break;
	case 4:
		cout << "Klient dostarczyl: " << endl << ">> ";
		cin >> nsprzet;
		osoba.Sprzet(nsprzet);
		break;
	default:
		goto wyb;
		break;
	};
	osoba.Status("Przyjete");
	osoba.Usluga_k("0");
	cout << "Opis Usterki: ";
	cin.ignore();
	getline(cin, nopis);
	osoba.Opis(nopis);

	string query = "INSERT INTO aktywne(imie,nazwisko,data_p,data_w,sprzet,status,usluga_k,opis) VALUES (\"" +
		osoba.Imie() + "\", \"" +
		osoba.Nazwisko() + "\", \"" +
		osoba.Data_pget() + "\", \"" +
		osoba.Data_wget() + "\", \"" +
		osoba.Sprzet() + "\", \"" +
		osoba.Status() + "\", \"" +
		osoba.Usluga_k() + "\", \"" +
		osoba.Opis() + "\")";
	if (ZapytanieDoBazy(query)) {
		cout << "Poprawnie dodano wpis do bazy danych!" << endl;
		system("pause");
	}
	else {
		return;
	}
	return;
};

#pragma endregion

#pragma region Funkcja_Wypisz

void Wypisz() {
	string query;
	system("cls");
	query = "SELECT * FROM aktywne";
	Connwyp(query);
	system("pause");
	return;
};

#pragma endregion

#pragma region Funcja_Wypisz_Zakonczone

void Wypiszzako() {
	string query;
	system("cls");
	query = "SELECT * FROM zakonczone";
	Connwyp(query);
	system("pause");
	return;
};

#pragma endregion

#pragma region Funkcja_Edytuj

void Edytuj() {
	int c;
	int id;
	int wyb;
	string c2;
	string statu;
	Osoba osoba;
	string nimie;
	string nnazwisko;
	string ndata_p;
	string ndata_w;
	string nsprzet;
	string nstatus;
	string nusluga_k;
	string nopis;
	string query;
	string tablica;
tablica: 
	cout << "Wybierz gdzie chcesz edytowac rekord :" << endl;
	cout << "1. Aktywne zgloszenia " << endl;
	cout << "2. Zakonczone zgloszenia " << endl;
	cout << "3. Powrot do menu !" << endl << ">> ";
	cin >> c;
	CzyszczenieBuff();
	if (c == 1) {
		tablica = "aktywne";
	}
	else if (c == 2) {
		tablica = "zakonczone";
	}
	else if (c == 3) {
		return;
	}
	else {
		goto tablica;
	}
	query = "SELECT * FROM " + tablica;
	Connwyp(query);
	cout << endl << "Wprowadz ID ktore chcesz edytowac" << endl << ">> ";
	cin >> id; 
	query = "SELECT COUNT(ID) FROM " + tablica + " WHERE ID = " + to_string(id);
	if (Connsprid(query)) {
		cout << "Podaj imie: ";
		cin >> nimie;
		osoba.Imie(nimie);
		cout << "Podaj nazwisko: ";
		cin >> nnazwisko;
		osoba.Nazwisko(nnazwisko);
		osoba.Data_pset(); 
		if (tablica == "zakonczone") {
			cout << "Czy chcesz edytowac date wydania ? t/n" << endl << ">> ";
			cin >> c2;
			CzyszczenieBuff();
			if (c2 == "t") {
				osoba.Data_wset();
			}
			else {
				query = "SELECT data_w FROM zakonczone WHERE id=" + to_string(id);
				osoba.Data_wset(PobierzDateWydania(query));
			}
		}
	wyb:
		wyb = 0;
		cout << "Jakie urzadzenie przyniosl klient?" << endl;
		cout << "1. Laptop" << endl;
		cout << "2. Komputer" << endl;
		cout << "3. Konsola" << endl;
		cout << "4. Inne urzadzenie" << endl << ">> ";
		cin >> wyb;
		CzyszczenieBuff();
		switch (wyb) {
		case 1:
			osoba.Sprzet("Laptop");
			break;
		case 2:
			osoba.Sprzet("Komputer");
			break;
		case 3:
			osoba.Sprzet("Konsola");
			break;
		case 4:
			cout << "Klient dostarczyl: " << endl << ">> ";
			cin >> nsprzet;
			osoba.Sprzet(nsprzet);
			break;
		default:
			goto wyb;
		}
	wyborstatusu:
		cout << "Podaj status" << endl;
		cout << "1. Realizacja" << endl;
		cout << "2. Naprawione" << endl;
		cout << "3. Odebrane" << endl;
		cout << "4. Anulowane" << endl;
		cin >> wyb;
		CzyszczenieBuff();
		switch (wyb) {
		case 1:
			osoba.Status("Realizacja");
			break;
		case 2:
			osoba.Status("Naprawione");
			break;
		case 3:
			osoba.Status("Odebrane");
			break;
		case 4:
			osoba.Status("Anulowane");
			break;
		default:
			goto wyborstatusu;
		};
		cout << "Podaj koszta uslugi: " << endl << ">> ";
		cin >> nusluga_k;
		osoba.Usluga_k(nusluga_k);
		cout << "Opis Usterki: ";
		cin.ignore();
		getline(cin, nopis);
		osoba.Opis(nopis);

		string query = "UPDATE " + tablica + " SET " +
			"imie=\"" + osoba.Imie() + "\"," +
			"nazwisko=\"" + osoba.Nazwisko() + "\"," +
			"data_p=\"" + osoba.Data_pget() + "\"," +
			"data_w=\"" + osoba.Data_wget() + "\"," +
			"sprzet=\"" + osoba.Sprzet() + "\"," +
			"status=\"" + osoba.Status() + "\"," +
			"usluga_k=\"" + osoba.Usluga_k() + "\"," +
			"opis=\"" + osoba.Opis() + "\"WHERE id=" + to_string(id);
		if (ZapytanieDoBazy(query)) {
			cout << "Poprawnie edytowano wpis w bazie danych!" << endl;
			system("pause");
			return;
		}
		else {
			return;
		}
	}
	else {
		cout << "Wprowadzono nie poprawne ID!!" << endl;
		system("pause");
		return;
	}
};

#pragma endregion

#pragma region Funkcja_Edytuj_Status

void Edytujstatus() {
	Osoba osoba;
	int wyb;
	int id;
	int kwota;
	string c;
	system("cls");
	string query = "SELECT * FROM aktywne";
	Connwyp(query);
wyborid:
	cout << "Czy napewno chcesz zmienic status ? t/n" << endl << ">> ";
	cin >> c;
	CzyszczenieBuff();
	if (c == "n") {
		return;
	}
	else {
		cout << endl << "Wprowadz ID w ktorym chcesz zmienic status: " << endl << ">> ";
		cin >> id;
		query = "SELECT COUNT(ID) FROM aktywne WHERE ID=" + to_string(id);
		if (Connsprid(query)) {
		wybor2status:
			cout << endl << "Na jakis status chcesz zamienic ?" << endl;
			cout << "1. Realizacja" << endl;
			cout << "2. Naprawione" << endl;
			cout << "3. Odebrane" << endl;
			cout << "4. Anulowane" << endl;
			cout << "5. Powrot do menu!" << endl << ">> ";
			cin >> wyb;
			CzyszczenieBuff();
			switch (wyb) {
			case 1:
				osoba.Status("Realizacja");
				query = "UPDATE aktywne SET status=\"" + osoba.Status() + "\" WHERE aktywne.ID=" + to_string(id);
				if (ZapytanieDoBazy(query)) {
					cout << "Poprawnie ustawiono status w bazie danych!" << endl;
				}
				else {
					return;
				}
				system("pause");
				return;
				break;
			case 2:
				osoba.Status("Naprawione");
				query = "UPDATE aktywne SET status=\"" + osoba.Status() + "\" WHERE aktywne.ID=" + to_string(id);

				if (ZapytanieDoBazy(query)) {
					cout << "Poprawnie ustawiono status w bazie danych!" << endl;
				}
				else {
					return;
				}
				system("pause");
				return;
				break;
			case 3:
			wybor3kwota:
				cout << "Wprowadz koncowa kwote jaka zaplacil klient" << endl << ">> ";
				cin >> kwota;
				cout << "Wpisana kwota to: " << kwota << endl << "Czy chcesz poprawic? t/n" << endl << ">> ";
				cin >> c;
				if (c == "t") {
					goto wybor3kwota;
				}
				osoba.Usluga_k(to_string(kwota));
				query = "UPDATE aktywne SET usluga_k=\"" + osoba.Usluga_k() + "\" WHERE aktywne.ID=" + to_string(id);
				if (ZapytanieDoBazy(query)) {
					cout << "Poprawnie edytowano koszt uslugi w bazie" << endl;
					osoba.Status("Odebrane");
					query = "UPDATE aktywne SET status=\"" + osoba.Status() + "\" WHERE aktywne.ID=" + to_string(id);
					if (ZapytanieDoBazy(query)) {
						cout << "Poprawnie ustawiono status w bazie danych!" << endl;
						osoba.Data_wset();
						query = "UPDATE aktywne SET data_w=\"" + osoba.Data_wget() + "\" WHERE aktywne.ID=" + to_string(id);
						if (ZapytanieDoBazy(query)) {
							cout << "Poprawnie ustawiono date wydania w bazie danych!" << endl;
							Przenies(id);
						}
						else {
							return;
						}
					}
					else {
						return;
					}
				}
				else {
					return;
				}
				return;
				break;
			case 4:
				osoba.Status("Anulowane");
				query = "UPDATE aktywne SET status=\"" + osoba.Status() + "\" WHERE aktywne.ID=" + to_string(id);
				if (ZapytanieDoBazy(query)) {
					cout << "Poprawnie ustawiono status w bazie danych!" << endl;
					osoba.Data_wset();
					query = "UPDATE aktywne SET data_w=\"" + osoba.Data_wget() + "\" WHERE aktywne.ID=" + to_string(id);
					if (ZapytanieDoBazy(query)) {
						cout << "Poprawnie ustawiono date wydania w bazie danych!" << endl;
						Przenies(id);
					}
					else {
						return;
					}
				}
				else {
					return;
				}
				return;
				break;
			case 5:
				return;
				break;
			default:
				goto wybor2status;
			}
		}
		else {
			goto wyborid;
		}
	}
	return;
};

#pragma endregion



#pragma region Funkcja_Menu

void Menu() {
wybor:
	int wyb;
	system("cls");
	cout << "\t\t\t\t\t\tAsystent Serwisu" << endl;
	cout << "1. Dodaj nowe zgloszenie serwisowe" << endl;
	cout << "2. Wyswietl aktualne zgloszenia" << endl;
	cout << "3. Edytuj zgloszenie" << endl;
	cout << "4. Wyswietl zakonczone/anulowane zgloszenia" << endl;
	cout << "5. Edytuj status" << endl;
	cout << "6. Wyjscie z programu!" << endl << ">> ";

	cin >> wyb;
	CzyszczenieBuff();
	switch (wyb) {
	case 1:
		Dodaj();
		goto wybor;
		break;
	case 2:
		Wypisz();
		goto wybor;
		break;
	case 3:
		Edytuj();
		goto wybor;
		break;
	case 4:
		Wypiszzako();
		goto wybor;
		break;
	case 5:
		Edytujstatus();
		goto wybor;
		break;
	case 6:
		system("exit");
		break;
	default:
		goto wybor;
		break;
	};
};

#pragma endregion