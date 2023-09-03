#include<iostream>

using namespace std;
/*
	���󹤳�ģʽ
	���ж�������Ʒ�࣬ÿ�������Ʒ��ʾͬһ���͵Ĳ�Ʒ
	ÿ�������Ʒ�о����Ʒ�࣬���Ա�ʾ��ͬ��˾��ͬ���Ͳ�Ʒ
	��һ�����󹤳���
	ÿ�����幤�����ʾ����ĳһ����˾�������Ͳ�Ʒ�Ĺ���
	�ŵ㣺
		�û�����ָ������Ʒ�ƣ�ֻ��Ҫ���幤���Ϳ��ԣ�����һ��Ʒ�Ʋ�Ʒ��ֻҪ����µĹ�����ֻ��չ�����Ͽ���ԭ��
	ȱ�㣺
		�и�Ʒ�ƶ���һ�ֲ�Ʒ�Ļ���Ҫ�ӵ���ܶ࣬�����Ʒ�ĳ����࣬����ʵ�֣�Ʒ�ƹ����ڲ������ĺ����������Ͽ���ԭ��
*/
// ��������Ʒ�࣬ÿ�������Ʒ���ʾһ������Ĳ�Ʒ
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

//ÿ�ֳ����Ʒ�ľ����Ʒ��
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

//���󹤳�
class Factory {
public:
	virtual Clothe* createClothe() = 0;
	virtual Shoes* createShoes() = 0;
	virtual ~Factory() {
		cout << "Abstract factory destroyed" << endl;
	}
};

//���幤����ÿ������������ÿ��Ʒ�Ƶ����в�Ʒ����ÿ��Ʒ�ƶ���ϵ�в�Ʒ֮���ٳ��󹤳���
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