#include<iostream>

using namespace std;

class Drink {
public:
	virtual int getVol() = 0;
	virtual void getSort() = 0;
	int vol;
	virtual ~Drink() {
		cout << "Abstract drink done." << endl;
	}
};

class Cola :public Drink {
public:
	Cola(int vol_) {
		vol = vol_;
	}
	int getVol() {
		return vol;
	}
	void getSort() {
		cout << "A cup of cola has been produced" << endl;
	}
	~Cola() {
		cout << "cola done." << endl;
	}
};

class Coffee : public Drink {
public:
	Coffee(int vol_) {
		vol = vol_;
	}
	int getVol() {
		return vol;
	}
	void getSort() {
		cout << "A cup of cola has been produced" << endl;
	}
	~Coffee() {
		cout << "coffee done." << endl;
	}
};


class Factory {
public:
	virtual Drink* createDrink() = 0;
	virtual ~Factory() {
		cout << "Abstract factory destoryed" << endl;
	}
};


class ColaFactory : public Factory {
public:
	Drink* createDrink() {
		return new Cola(250);
	}
	~ColaFactory() {
		cout << "Cola factory destroyed" << endl;
	}
};

class CoffeeFactory :public Factory {
	Drink* createDrink() {
		return new Coffee(500);
	}
	~CoffeeFactory() {
		cout << "Coffee factory destroyed" << endl;
	}
};


int main() {
	Factory* colafactory = new ColaFactory();
	Drink *cola = colafactory->createDrink();
	Factory* coffeefactory = new CoffeeFactory();
	Drink* coffee = coffeefactory->createDrink();
	cout << cola->getVol() << endl;
	cola->getSort();
	cout << coffee->getVol() << endl;
	coffee->getSort();
	delete cola;
	delete colafactory;
	delete coffee;
	delete coffeefactory;
	
	

}