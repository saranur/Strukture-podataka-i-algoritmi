#include  <iostream>
using namespace  std;

typedef int Tip; 

struct Cvor
{
	Cvor* next = nullptr; //pokazivac na naredni element u nizu/listi 
	Tip info;
	Cvor(Tip info, Cvor* next)
	{
		this->info = info;
		this->next = next;
	}
};

class Red
{
public:
	virtual void dodaj(Tip v) = 0;
	virtual Tip ukloni() = 0;
	virtual bool IsPrazan() = 0;
};
class RedSekv : public Red
{
	int max = 10;
	int pocetak = 0;
	int kraj = 0;
	int brojac = 0;
	int* N = new int[max];

public:
	void dodaj(Tip v)
	{
		if (max == brojac)
			throw exception("Greska! Red je pun.");
		N[kraj] = v;
		kraj++;
		brojac++;
		if (kraj == max)
			kraj = 0;

	}
	Tip ukloni()
	{
		if (brojac == 0)
			throw exception("Greska! Red je prazan.");

		int x = N[pocetak];
		pocetak++;
		if (pocetak == max)
			pocetak = 0;
		brojac--;
		return x;
	}
	bool IsPrazan() 
	{
		if (pocetak == kraj)
			return true;
		return false;
	}

};

class RedPov : public Red
{
	Cvor* kraj = nullptr;
	Cvor* pocetak = nullptr;
public:
	void dodaj(Tip v)
	{
		Cvor* t = new Cvor(v, nullptr);
		if (pocetak != nullptr)
		{
			kraj->next=t;
			kraj = t;
		}
		else
		{
			kraj = t;
			pocetak = t;
		}
	}
	Tip ukloni() 
	{
		if (IsPrazan())
			throw exception("Greska! Red je prazan!");
		Cvor* t= pocetak;
		pocetak = pocetak->next;
		Tip x= t->info;
		delete t;
		//U slucaju da je red prazan, prvi element ce pokazivati na nullptr
		//Tada moramo i kraj staviti na nullptr jer ne moze samo pocetak pokazivati na nullptr
		if (pocetak == nullptr)
			kraj = nullptr;
		return x;
	}
	bool IsPrazan()
	{
		if(pocetak == nullptr)
			return true;
		return false;
	}
};

void Ispis(Red&R)
{
	
	for (int i = 0; i < 10; i++)
	{
		cout << " ";
		R.dodaj(i);
	} cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << " ";
		cout << R.ukloni();
	} cout << endl;

}
void main()
{
	RedSekv r1;
	RedPov r2;
	cout << "Red sekvencijalno" << endl;
	cout << "----------------------------------------" << endl;
	Ispis(r1);
	cout << "----------------------------------------" << endl;
	cout << "Red povezano" << endl;
	cout << "----------------------------------------" << endl;
	Ispis(r2);
	cout << "----------------------------------------" << endl;


}