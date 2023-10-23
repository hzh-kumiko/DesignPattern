#include<iostream>
#include<memory>

/*
�����ԣ��������е����������ӿڽ���Э����ʹ�����ܹ�һ�������������޸���Դ���롣

�����ԣ������������е��࣬������Ϊ����Ӧ�½ӿڶ��޸����ǡ�

�����ԣ������������뵽������ͬ�ӿ�֮�䣬ʹ�����໥��������������϶ȡ�

��װ�ԣ������������˱������ߵľ���ʵ��ϸ�ڣ��Կͻ����ṩ��һ������Ľӿڡ�

����ϵͳ��֧�֣�����Ҫʹ�þɵġ������ݵ���ʱ������ʹ������������ӿ�ת�����µĽӿڡ�
*/
//��Ҫ�Ľӿ�
class Target {
public:
	virtual void request() {}
};

//�������ߣ�ԭ�е���Ҫת���������Ҫ�Ľӿڵ���
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

//������������������ת����Ŀ���࣬���Ե��ñ������ߵķ���
//���������ͻ��˺ͱ������߽���ͻ��˲���Ҫ֪���������ߵľ���ʵ�֣�ֻ��Ҫͨ�����������н�����
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
