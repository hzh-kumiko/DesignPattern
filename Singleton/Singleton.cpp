#include<iostream>
#include<map>
#include<vector>
#include<memory>
#include<mutex>
#include<vld.h>
using namespace std;

/*
class Database {
protected:
	Database() {}
public:
	static Database& get() {
		static Database database;
		return database;
	}
	static Database& get1() {
		static Database* database1 = new Database();
		return *database1;
	}
	~Database() {
		cout << "xigou" << endl;
	}

	Database( const Database &) = delete;
	Database(Database&&) = delete;
	Database& operator=(const Database&) = delete;
	Database& operator=(Database&&) = delete;


};
*/

// 数据库抽象类
class Database {
public:
	virtual int get_population(const string& name) = 0;
	virtual ~Database() {
		cout << "xigou" << endl;
	}
};

// 懒汉式单例
// 只有在需要的时候获取对象，调取相应函数
class SingletonDatabase :public Database {
private:
	static SingletonDatabase* m_db;
	static mutex m_mutex;
	SingletonDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		//读取数据库内容的操作，这里简单定义存了两个数据
	}
	~SingletonDatabase() {
		cout << "单例析构" << endl; 
	}
	map<string, int> capitals;
public:
	SingletonDatabase(SingletonDatabase const&) = delete;
	SingletonDatabase& operator=(SingletonDatabase const&) = delete;
	//移动构造也可以设置为delete

	//方法一：静态函数获取，只有一个实例，只是读取，线程安全
	static SingletonDatabase& get() {
		static SingletonDatabase db;
		return db;
	}
	/*
	static SingletonDatabase& get() {
		static shared_ptr<SingletonDatabase> db(new SingletonDatabase);
		return *db;
	}
	*/
	//方法二：双检锁，线程安全，但双检锁会存在问题
	//线程 A 进入实例，执行 pInstance 的第一次测试，获取锁，并执行由步骤 1 和 3 组成的语句。然后它被挂起。 
	//此时 pInstance 是非空的，但在 pInstance 指向的内存中还没有构造 Singleton 对象。
	//线程 B 进入实例，确定 pInstance 不为空，并且将其返回给实例的调用者。 然后调用者取消引用指针访问尚未构建的单例。
	
	static SingletonDatabase*& get1() {
		if (m_db == nullptr) {
			lock_guard<mutex> mylock(m_mutex);
			if (m_db == nullptr) {
				m_db = new (nothrow) SingletonDatabase;
			}
		}
		return m_db;
	}
	static void del() {
		lock_guard<mutex> mylock(m_mutex);
		if (m_db) {
			delete m_db;
			m_db = nullptr;
		}
	}
	
	int get_population(const string& name) {
		return capitals[name];
	}

};
SingletonDatabase *SingletonDatabase::m_db = nullptr;
mutex SingletonDatabase::m_mutex;


class SingletonRecordFinder {
public:
	explicit SingletonRecordFinder(Database& db_) :db(db_) {
	}
	int total_population(vector<string> names) {
		int result = 0;
		for (auto& name : names) {
			result += db.get_population(name);
		}
		return result;
	}
	Database& db;
};

//测试案例，这不是只能生成唯一实例，仅测试数据是否创建正确
class DummyDatabase :public Database {
private:
	map<string, int> capitals;
public:
	DummyDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
	}
	int get_population(const string& name) {
		return capitals[name];
	}
};

//以上是懒汉式创建，只在需要时获取唯一实例

//饿汉式单例模式 在一开始就创建，线程安全
class HungrySingleton : public Database {
public:
	static HungrySingleton& get();
	static void del();
	int get_population(const string& name) {
		return capitals[name];
	}
private:
	static HungrySingleton m_db;
	static mutex m_mutex;
	HungrySingleton() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		//读取数据库内容的操作，这里简单定义存了两个数据
	}
	~HungrySingleton() {
		cout << "饿汉单例析构" << endl;
	}
	map<string, int> capitals;

};


HungrySingleton HungrySingleton::m_db;
mutex HungrySingleton::m_mutex;
HungrySingleton& HungrySingleton::get() {
	return m_db;
}

/*void HungrySingleton::del() {
	lock_guard<mutex> mylock(m_mutex);
	if (m_db) {
		delete m_db;
		m_db = nullptr;
	}
}*/
int main() {
	
	//用静态变量获取
	// SingletonRecordFinder rf(SingletonDatabase::get()); //用不到del
	//如果双检索创建 用del防止内存泄漏，双检锁会有问题，不建议
	SingletonRecordFinder rf(*SingletonDatabase::get1()); // get1() 创建了实例，通过构造函数，初始化rf
	vector<string> names{ "alpha","beta" };
	int tp = rf.total_population(names);
	cout << tp << endl;;
	SingletonDatabase::del();

	SingletonRecordFinder rf1(HungrySingleton::get());
	cout << rf1.total_population(names) << endl;
	//HungrySingleton::del();
	
	
}