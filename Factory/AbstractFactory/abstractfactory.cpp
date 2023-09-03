#include<iostream>

using namespace std;

class Shoes {
public:
	virtual void create() = 0;
	virtual ~Shoes(){
		cout << "Abstract shoes done." << endl;
	}
};

class Clothe {
public:
	virtual void create() = 0;
	virtual ~Clothe() {
		cout << "Abstract sclothe done." << endl;
	}
};

class NikeShoes :public Shoes {
public:
	void create() {
		cout << "A Nike shoes has been produced" << endl;
	}
	~NikeShoes() {
		cout << "Nike shoes done." << endl;
	}
};

class NikeClothe :public Clothe {
public:
	void create() {
		cout << "A Nike clothe has been produced" << endl;
	}
	~NikeClothe() {
		cout << "Nike clothe done." << endl;
	}
};

class AdiShoes:public Shoes {
public:
	void create() {
		cout << "A Adi shoes has been produced" << endl;
	}
	~AdiShoes() {
		cout << "Adi shoes done." << endl;
	}
};

class AdiClothe :public Clothe {
public:
	void create() {
		cout << "A Adi clothe has been produced" << endl;
	}
	~AdiClothe() {
		cout << "Adi clothe done." << endl;
	}
};

class Factory {
public:
	virtual Clothe* createClothe() = 0;
	virtual Shoes* createShoes() = 0;
	virtual ~Factory() {
		cout << "Abstract factory destroyed" << endl;
	}
};

class NikeFactory :public Factory {
	Clothe* createClothe() {
		return new NikeClothe();
	}
	Shoes* createShoes() {
		return new NikeShoes();
	}
	~NikeFactory() {
		cout << "nike factory has been destroyed" << endl;
	}
};

class AdiFactory :public Factory {
	Clothe* createClothe() {
		return new AdiClothe();
	}
	Shoes* createShoes() {
		return new AdiShoes();
	}
	~AdiFactory() {
		cout << "Adi factory has been destroyed" << endl;
	}
};

int main() {
	Factory* nikefactory = new NikeFactory();
	Shoes* nikeshoes = nikefactory->createShoes();
	nikeshoes->create();
	delete nikeshoes;
	delete nikefactory;
}