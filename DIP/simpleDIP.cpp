#include<iostream>


using namespace std;

/*
�����
*/

class HardDisk {
public:
	virtual void work() = 0;
};

class Memory {
public:
	virtual void work() = 0;
};

class CPU {
public:
	virtual void work() = 0;
};

/*
�߼��ܹ��㣬�ÿ�ܺ;���ĵ��Բ�Ʒ����������м�����
*/
class Computer {
public:
	Computer(HardDisk* myHardDisk_, Memory* myMemory_, CPU* myCpu_) :myHardDisk(myHardDisk_), myMemory(myMemory_), myCpu(myCpu_) {}
	void work() {
		myHardDisk->work();
		myMemory->work();
		myCpu->work();
	}
private:
	HardDisk* myHardDisk;
	Memory* myMemory; 
	CPU* myCpu;
};

/*
�ײ�ʵ�ֲ㣬ֻ���������Ľӿڣ�ʵ�ֳ����ķ���
*/
class XiJieHardDisk :public HardDisk {
	void work() {
		cout << "XiJie HardDisk working" << endl;
	}
};

class IntelCpu :public CPU {
	void work() {
		cout << "Inter CPU working" << endl;
	}
};

class JSDMemory :public Memory {
	void work() {
		cout << "JSD Memory working" << endl;
	}
};

int main() {
	HardDisk* xjdisk = new XiJieHardDisk;
	CPU* iCpu = new IntelCpu;
	Memory* jsdm = new JSDMemory;
	Computer* myComp = new Computer(xjdisk, jsdm, iCpu);
	myComp->work();
	delete xjdisk;
	delete iCpu;
	delete jsdm;
	delete myComp;

}