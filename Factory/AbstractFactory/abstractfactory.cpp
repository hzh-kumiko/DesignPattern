#include<iostream>

using namespace std;
/*
	抽象工厂模式
	会有多个抽象产品类，每个抽象产品表示同一类型的产品
	每个抽象产品有具体产品类，可以表示不同公司的同类型产品
	有一个抽象工厂类
	每个具体工厂类表示生产某一个公司所有类型产品的工厂
	优点：
		用户不用指定具体品牌，只需要具体工厂就可以，新增一个品牌产品族只要添加新的工厂，只扩展，符合开闭原则
	缺点：
		有个品牌多了一种产品的话，要加的类很多，比如产品的抽象类，具体实现，品牌工厂内部生产的函数，不符合开闭原则
*/
// 多个抽象产品类，每个抽象产品类表示一个种类的产品
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

//每种抽象产品的具体产品类
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

//抽象工厂
class Factory {
public:
	virtual Clothe* createClothe() = 0;
	virtual Shoes* createShoes() = 0;
	virtual ~Factory() {
		cout << "Abstract factory destroyed" << endl;
	}
};

//具体工厂，每个工厂内生产每个品牌的所有产品，当每个品牌多了系列产品之后再抽象工厂中
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