#include<iostream>


/*
װ����ģʽ����Ҫ�������ڶ�̬�ظ�һ��������Ӷ���Ĺ��ܣ����ҿ����ڲ�Ӱ���������������£�������չ���ܡ���ʹ�����ǳ���������Ҫ��̬����ǿ����������ܵ������ͬʱҲ������ͨ���̳����������������ࡣ

�ܵ���˵��װ����ģʽ����ʹ����Ĺ�����չ������ͬʱҲ��������ӿڵļ���������
*/
class Coffee
{
public:
	virtual double getPrice() const = 0;

};

class Espresso :public Coffee {
public:
	double getPrice() const override {
		return 1.0;
	}
};

class Decorator :public Coffee {
protected:
	Coffee* coffee;
public:
	Decorator(Coffee* coffee_) :coffee(coffee_) {}
	double getPrice() const override {
		return coffee->getPrice();
	}
};

class MilkDecorator :public Decorator {
public:
	MilkDecorator(Coffee* coffee_) :Decorator(coffee_) {}
	double getPrice() const override {
		return coffee->getPrice() + 0.8;
	}
};

class SugarDecorator :public Decorator {
public:
	SugarDecorator(Coffee* coffee_) :Decorator(coffee_) {}
	double getPrice() const override {
		return coffee->getPrice() + 0.3;
	}
};



int main() {
	Coffee* coffee = new Espresso;
	Decorator* milkCoffee = new  MilkDecorator(coffee);
	Decorator* sugarCoffee = new  SugarDecorator(coffee);
	Decorator* milkSugarCoffee = new SugarDecorator(milkCoffee);
	std::cout << "a cup of Espresso: " << coffee->getPrice() << std::endl;
	std::cout << "a cup of Espresso with milk: " << milkCoffee->getPrice() << std::endl;
	std::cout << "a cup of Espresso with sugar: " <<sugarCoffee->getPrice() << std::endl;
	std::cout << "a cup of Espresso with milk and sugar: " << milkSugarCoffee->getPrice() << std::endl;
}