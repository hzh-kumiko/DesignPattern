#include<vector>
#include<iostream>
#include<mutex>

using namespace std;

template<typename T>
class Observer;

// 被观察者的基类： 可以添加观察者订阅，取消观察者订阅，以及当状态变更时通知每个观察者
// 所以有一个观察者列表，当用户订阅时添加到列表中，取消时将列表中该用户删除（在这里将其置空），
// 被观察的对象如果状态更新通知列表中每一个用户
// 被观察对象的派生类： 里面有每种对象具体的状态变量，设置状态变量值，在这里如果设置后的状态满足
// 一定条件就会调用notify观察者，调用观察者的field_changed函数，告诉他状态已经变了

// 观察者的抽象类
// 观察者的具体类，表明观察的是哪个对象类，这里的代码具体到了表明观察的是某种对象的某种具体信息，
// 观察者收到通知后根据状态变更信息来判断是不是可以下一步操作
template<typename T>
class Observable {
public:
	Observable() : followers(0) {}

	//观察对象基类发送信息给所有观察者
	void notify(T& source, const string& name) {
		vector<Observer<T>*> observers_copy;
		{
			lock_guard<mutex> mylock(my_mutex);
			observers_copy = observers;
		}
		for (auto& ob : observers_copy) {
			if (ob) {
				ob->field_changed(source, name);
			}
		}
	}

	void subscribe(Observer<T>* ob) {
		lock_guard<mutex> mylock(my_mutex);
		if (count(observers.begin(), observers.end(), ob) == 0) {
			observers.push_back(ob);
			followers++;
		}
		
		cout << "Now you have " << followers << " subscribers" << endl;
	}
	void unsubscribe(Observer<T>* ob) {
		lock_guard<mutex> my_lock(my_mutex);
		auto it = find(observers.begin(), observers.end(), ob);
		if (it != observers.end()) { 
			*it = nullptr;
			followers--;
			cout << "Now you have " << followers << " subscribers" << endl;
		}
		else {
			cout << "You need to subscribe first." << endl;
		}
	}
private:
	vector<Observer<T>*> observers;
	mutable mutex my_mutex;
	int followers;
};


class Person : public Observable<Person> {
private:
	int age;
	string new_name;
	string old_name;
public:
	Person(int age_,const string& name_) :age(age_), new_name(name_),old_name("") {}
	int get_age() {
		return age;
	}
	string get_newname() {
		return new_name;
	}
	string get_oldname() {
		return old_name;
	}
	//对象的状态改变，当观察对象的状态到期望时，会notify所有观察者
	void set_age(int age_) {
		if (age_ == age) {
			return;
		}
		age = age_;
		if (age >= 16) {
			notify(*this, "age");
		}
	}
	void set_name(const string& name_) {
		if (name_ == new_name) {
			return;
		}
		old_name = new_name;
		new_name = name_;
		notify(*this, "name");
	}

};

template<typename T>
class Observer {
public:
	virtual void field_changed(T& source, const string& name) = 0;
};

template<typename T>
class age_Observer :public Observer<T> {
public:
	age_Observer() :vote(false), drive(false) {}
	void field_changed(T& source, const string& name)  {
		if (name == "age") {
			int age = source.get_age();
			cout << "Person' s " << name << "is now " << age << endl;
			if (age >= 16 && vote == false) {
				vote = true;
				cout << source.get_newname() << " has the vote right now." << endl;
			}
			else if (age >= 18 && drive == false) {
				drive = true;
				cout << source.get_newname() << " can learn how to drive." << endl;
			}
		}
			

	}
private:
	bool vote;
	bool drive;
};

template<typename T> 
class name_Observer :public Observer<T> {
public:
	void field_changed(T& source, const string& name) {
		if (name == "name") 
			cout << "The person " << source.get_oldname() << " now changed his/her name to " << source.get_newname() << endl;
	}
};


int main() {
	Person pa(15, "张三");
	Observer<Person>* ob_page = new age_Observer<Person>(); 
	Observer<Person>* ob_pname = new name_Observer<Person>();
	//被观察对象被人订阅
	pa.subscribe(ob_page); //只观察年龄变化
	pa.subscribe(ob_pname); //只观察名字变化
	//被观察对象年龄增长
	pa.set_age(16);
	//观察者对象改名
	pa.set_name("张四");
	pa.set_age(18);
	pa.unsubscribe(ob_page);
	pa.unsubscribe(ob_pname);
	delete ob_pname;
	delete ob_page;

}