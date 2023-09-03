#include<iostream>

using namespace std;
/*
	一个抽象产品类
	多个具体产品类
	一个抽象工厂类
	多个具体工厂类
	一个具体产品对应一个具体工厂
	符合开闭原则
	当有一个新产品时加一个具体产品类合一个具体工厂类
	需要的类可能很多
*/
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