#include<iostream>
#include<memory>

/*
兼容性：允许已有的类与其他接口进行协作，使它们能够一起工作，而无需修改其源代码。

复用性：可以重用已有的类，而无需为了适应新接口而修改它们。

解耦性：将适配器插入到两个不同接口之间，使它们相互独立，减少了耦合度。

封装性：适配器隐藏了被适配者的具体实现细节，对客户端提供了一个抽象的接口。

遗留系统的支持：当需要使用旧的、不兼容的类时，可以使用适配器将其接口转换成新的接口。
*/
//需要的接口
class Target {
public:
	virtual void request() {}
};

//被适配者，原有的需要转变成我们需要的接口的类
class Adaptee {
public:
	Adaptee() { std::cout << "init" << std::endl; }
	Adaptee(const Adaptee& p) {
		std::cout << "copy" << std::endl;
	}
	void specificRequest() {
		std::cout << "This is the specific interface the target needs" << std::endl;
	}
};

//适配器，将被适配者转换成目标类，可以调用被适配者的方法
//适配器将客户端和被适配者解耦，客户端不需要知道被适配者的具体实现，只需要通过适配器进行交互。
class Adapter:public Target
{
private:
	Adaptee* adaptee;
public:
	Adapter(Adaptee* _adaptee) :adaptee(_adaptee) {}
	~Adapter() {
		delete adaptee;
	}
	void request()override {
		adaptee->specificRequest();
	}
};

int main() {
	Adaptee* myAdaptee = new Adaptee;
	Target* myTarget = new Adapter(myAdaptee);
	myTarget->request();
}
