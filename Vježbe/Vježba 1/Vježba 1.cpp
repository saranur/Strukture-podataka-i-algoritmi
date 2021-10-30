#include  <iostream>
using namespace  std;


class Osoba
{
public:
	int Id;
	string ime;
	Osoba()
	{

	}
	Osoba(int id, string ime)
	{
		this->ime = ime;
		this->Id = id;
	}
	virtual void info()
	{
		cout << "Ja sam osoba " << ime << endl;
	}
};
class Student : public Osoba
{
public:
	int brojIndeksa;
	Student(int id, string ime, int brojIndeksa) : Osoba(id, ime)
	{
		this->brojIndeksa = brojIndeksa;
	}
	void info()
	{
		cout << "Ja sam student " << ime << ". Broj indeksa = " << brojIndeksa << endl;
	}
};
class Stack
{

public:
	virtual void dodaj(int x) = 0;

	virtual int ukloni() = 0;

	virtual bool jel_prazna() = 0;
};


class Lista
{
	//Ako imamo jednu ili vise cistih virtualnih funkcija - ova klasa postaje apstraktna
//tj. mi ne mozemo napraviti objekat bazne klase, dakle u mainu ne mozemo napisati Lista x0

public:
	virtual void dodaj_na_pocetak(int x) = 0;
	//Cista virtualna funkcija - nema implementaciju u tijelu funkcije, odnosno nema definiciju u baznoj klasi
	//Znamo da je cisto virtuelna funkcija jer imamo =0. 

	virtual void dodaj_na_kraj(int x) = 0;

	virtual int ukloni_sa_pocetka() = 0;

	virtual int ukloni_sa_kraja() = 0;

	virtual bool jel_prazna() = 0;

	virtual int operator[](int index) = 0;

	virtual int get_brojac() = 0;
};



class ListaSekv : public Lista
	//ListaSekv znaci da cemo korisiti nizove za cuvanje dodatnih podataka
	//svaki x koji se doda dodaje se u niz
{
	int brojac = 0;
	int  max = 5;
	int* N = new int[max];
public:
	void prosiri_niz()
	{
		int* novi = new int[max + 10];
		for (int i = 0; i < max; i++)
		{
			novi[i] = N[i];
		}
		delete[] N;
		N = novi; //pokazivac preusmjeravmo na novi
		max += 10;
		cout << "Niz je prosiren sa " << max - 10 << " na " << max << endl;
	}
	void dodaj_na_pocetak(int x)
	{
		if (brojac == max)
			prosiri_niz();
		for (int i = brojac; i >= 1; i--)
			N[i] = N[i - 1];

		brojac++;
		N[0] = x;
	}
	int ukloni_sa_pocetka() {
		if (brojac == 0)
			throw exception("Greska! Lista je prazna");
		int x = N[0];
		for (int i = 0; i < brojac - 1; i++)
			N[i] = N[i + 1];

		brojac--;
		return x;

	}

	void dodaj_na_kraj(int x) {
		if (brojac == max)
			prosiri_niz();
		N[brojac] = x;
		brojac++;
	}



	int ukloni_sa_kraja() {

		if (brojac == 0)
			throw exception("Greska! Lista je prazna.");
		brojac--;
		int x = N[brojac];
		return x;
	}

	bool jel_prazna()
	{
		return brojac == 0;
	}

	int operator[](int index) {
		if (index<0 || index>max)
			throw exception("Greska! Indeks je neispravan");
		return N[index];
	}

	int get_brojac() {
		return brojac;
	}
};

class StackSekv : public Stack

{
	int brojac = 0;
	int  max = 5;
	int* N = new int[max];
public:
	void prosiri_niz()
	{
		int* novi = new int[max + 10];
		for (int i = 0; i < max; i++)
		{
			novi[i] = N[i];
		}
		delete[] N;
		N = novi; //pokazivac preusmjeravmo na novi
		max += 10;
		cout << "Niz je prosiren sa " << max - 10 << " na " << max << endl;
	}

	void dodaj(int x) {
		if (brojac == max)
			prosiri_niz();
		N[brojac] = x;
		brojac++;
	}

	int ukloni() {

		if (brojac == 0)
			throw exception("Greska! Stack je prazan.");
		brojac--;
		int x = N[brojac];
		return x;
	}

	bool jel_prazna()
	{
		return brojac == 0;
	}

};

typedef int Tip;

struct Cvor
{
	Cvor* next;
	Tip info;
	Cvor(Tip info, Cvor* next)
	{
		this->info = info;
		this->next = next;
	}
};

class ListaPov : public Lista
	/* kod ListaPov koristicemo dinamicku memoriju, odnosno cvorove u dinamickoj memoriji
	gdje svaki cvor cuva samo jedan podatak i onda se ti cvorovi povezuju.

	*/
{
	Cvor* prvi = nullptr;
	int brojac = 0;
public:
	void dodaj_na_pocetak(int x)
	{
		Cvor* n = new Cvor(x, prvi);
		prvi = n;
		brojac--;
	}
	int ukloni_sa_pocetka() {
		//	int x= prvi //ne mozemo pisati ovako jer je prvi tipa cvor
			//int x = (*prvi).info;
		int x = prvi->info; //kraci nacin pisanja, broj je kopiran u varijablu x
		Cvor* t = prvi; //pomocni pokazivac jer ne mozemo samo obrisati prvi , na ovaj nacin mozemo dealocirati prvi clan
		prvi = prvi->next;
		delete t;
		brojac++;
		return x;
	}

	void dodaj_na_kraj(int x) {
		if (prvi == nullptr) {
			//ako je lista prazna 
			prvi = new Cvor(x, nullptr);
			return;
		}
		Cvor* t = prvi;
		while (t->next != nullptr) {
			t = t->next;
		}
		t->next = new Cvor(x, nullptr);
	}


	int ukloni_sa_kraja() {
		//pt pokazuje na prethodni pokazivac, jer ukoliko uklonimo zadnji element, predzadnji element nece biti nullptr
		if (jel_prazna())
		{
			throw exception("Greska! Lista je prazna");
		}
		Cvor* pt = nullptr;
		Cvor* t = prvi;
		while (t->next != nullptr) {
			pt = t; //pt cuva vrijednost t- tako da nakon sto uklonimo zadnji clan, mozemo modifiktovati predzanji (moramo ga staviti na nullptr nakon uklanjanja zadnjeg clana)
			t = t->next; //prolazimo od prvog do zadnjeg clana
		}
		int x = t->info;
		delete t;
		if (pt != nullptr) {
			pt->next = nullptr; //nakon uklanjanja zadnjeg clana, prethodni pointer postavljamo na nula jer sada je on zadnji clan 	
		}
		else {
			//ako je lista imala jedan element
			prvi = nullptr;
		}
		return x;
	}

	bool jel_prazna()
	{
		return prvi == nullptr;
	}

	int operator[](int index) {
		Cvor* t = prvi;
		for (int i = 0; i < index; i++)
		{
			t = t->next;
		}
		return t->info;
	}

	int get_brojac() {
		return brojac;
	}
};

class StackPov : public Stack
	/* kod ListaPov koristicemo dinamicku memoriju, odnosno cvorove u dinamickoj memoriji
	gdje svaki cvor cuva samo jedan podatak i onda se ti cvorovi povezuju.

	*/
{
	Cvor* prvi = nullptr;
	int brojac = 0;
public:
	void dodaj(int x)
	{
		Cvor* n = new Cvor(x, prvi);
		prvi = n;
		brojac--;
	}
	int ukloni() {
		//	int x= prvi //ne mozemo pisati ovako jer je prvi tipa cvor
			//int x = (*prvi).info;
		int x = prvi->info; //kraci nacin pisanja, broj je kopiran u varijablu x
		Cvor* t = prvi; //pomocni pokazivac jer ne mozemo samo obrisati prvi , na ovaj nacin mozemo dealocirati prvi clan
		prvi = prvi->next;
		delete t;
		brojac++;
		return x;
	}

	bool jel_prazna()
	{
		return prvi == nullptr;
	}
};


void funkcija(Lista& L) //moguce je koristiti ovu funkciju jer smo stavili referencu (mozemo staviti i pokazivac)
{
	for (int i = 0; i < 10; ++i)
	{
		L.dodaj_na_pocetak(i); //trosenje vremena na pomjera svih elemenata pri dodavanju elementa na pocetak ili uklanjanju sa pocetka,
		//trosenje vremena, ukoliko imamo jako puno elementata to bi bila jako losa implementacija, npr za niz od 1000000 elemanata, for petlja bi dugo trajala
	}
	for (int i = 0; i < 10; ++i)
	{
		L.dodaj_na_kraj(i); //jako brzo se izvrsava jer samo dodaje jedan element na kraj niza
	}
	for (int i = 0; i < 3; ++i)
	{
		cout << "uklonjeno sa sa pocetka: " << L.ukloni_sa_pocetka() << endl; //isti nedostatak kao i za dodavanje na pocetak
	}

	for (int i = 0; i < 12; ++i)
	{
		cout << "uklonjeno sa kraja: " << L.ukloni_sa_kraja() << endl; //jako brzo izvrsavanje jer samo uzmemo broj s kraja
	}

	while (!L.jel_prazna())
	{
		cout << "uklonjeno sa pocetka: " << L.ukloni_sa_pocetka() << endl;
	}
}

void funkcija(Stack& L) //moguce je koristiti ovu funkciju jer smo stavili referencu (mozemo staviti i pokazivac)
{
	for (int i = 0; i < 10; ++i)
	{
		L.dodaj(i);
	}
	while (!L.jel_prazna())
	{
		cout << "uklonjeno sa pocetka: " << L.ukloni() << endl;
	}
}

void main()
{
	ListaSekv x1; //Sekvencijalno
	ListaPov x2;  //Povezano

	//Lista& x0 = x1;
	//Lista* p = &x1;
	//Lista* p2 = &x2;
	//Lista* p3 = new ListaSekv;

	funkcija(x1);  //obje liste (klase) saljemo u funkciju, ovo je moguce ako obje imaju istu baznu klase ili ako je jedna drugu naslijedila 

	//funkcija(x2);
	StackSekv s1;
	StackPov s2;
	cout << "Stack sekvencijalni" << endl;
	funkcija(s1);
	cout << "Stack povezani" << endl;
	funkcija(s2);


}