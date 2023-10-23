#include<iostream>


using namespace std;

/*
抽象层
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
高级架构层，让框架和具体的电脑产品解耦，依赖于中间抽象层
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
底层实现层，只依赖抽象层的接口，实现抽象层的方法
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