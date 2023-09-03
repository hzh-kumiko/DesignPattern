#include<iostream> 


using namespace std;
/*
	一个抽象产品类
	多个具体产品类
	一个具体工厂类
	在一个工厂内实现判断要生产哪一种产品
	不符合开闭原则，当有新产品时会在工厂类内部加新的实现
	结构简单
*/
class Product {
public:
	Product(int r):x(r){}
	virtual int getSize() = 0;
	virtual void getShape() = 0;
	virtual ~Product() {
		cout << "product done" << endl;
	}
	int x;	
};

class Circle : public Product {
public:
	Circle(int r) :Product(r) {}
	int getSize() {
		return this->x;
	}
	void getShape() {
		cout << "It is a circle" << endl;
	}
	~Circle() {
		cout << "Circle done" << endl;
	}
};

class Retangle : public Product {
public:
	Retangle(int r) :Product(r) {}
	int getSize() {
		return this->x;
	}
	void getShape() {
		cout << "It is a retangle" << endl;
	}
	~Retangle() {
		cout << "retangle done" << endl;
	}
};

class SimpleFactory {
public:
	Product* createProduct(int type) {
		if (type == 1) {
			return new Retangle(3);
		}
		else if (type == 2) {
			return new Circle(5);
		}
	}
	~SimpleFactory() {
		cout << "SimpleFactory destroyed" << endl;
	}
};
int main() {
	SimpleFactory f1;
	Product *p1 = f1.createProduct(1);
	p1->getShape();
	delete p1;
}