#include<iostream>


/*
装饰器模式的主要作用在于动态地给一个对象添加额外的功能，而且可以在不影响其他对象的情况下，灵活地扩展功能。这使得它非常适用于需要动态地增强或减弱对象功能的情况，同时也避免了通过继承来创建大量的子类。

总的来说，装饰器模式可以使得类的功能扩展更加灵活，同时也保持了类接口的简洁和清晰。
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