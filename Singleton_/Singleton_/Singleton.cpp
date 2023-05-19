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

// ���ݿ������
class Database {
public:
	virtual int get_population(const string& name) = 0;
	virtual ~Database() {
		cout << "xigou" << endl;
	}
};

// ����ʽ����
// ֻ������Ҫ��ʱ���ȡ���󣬵�ȡ��Ӧ����
class SingletonDatabase :public Database {
private:
	static SingletonDatabase* m_db;
	static mutex m_mutex;
	SingletonDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		//��ȡ���ݿ����ݵĲ���������򵥶��������������
	}
	~SingletonDatabase() {
		cout << "��������" << endl; 
	}
	map<string, int> capitals;
public:
	SingletonDatabase(SingletonDatabase const&) = delete;
	SingletonDatabase& operator=(SingletonDatabase const&) = delete;
	//�ƶ�����Ҳ��������Ϊdelete

	//����һ����̬������ȡ��ֻ��һ��ʵ����ֻ�Ƕ�ȡ���̰߳�ȫ
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
	//��������˫�������̰߳�ȫ����˫�������������
	//�߳� A ����ʵ����ִ�� pInstance �ĵ�һ�β��ԣ���ȡ������ִ���ɲ��� 1 �� 3 ��ɵ���䡣Ȼ���������� 
	//��ʱ pInstance �Ƿǿյģ����� pInstance ָ����ڴ��л�û�й��� Singleton ����
	//�߳� B ����ʵ����ȷ�� pInstance ��Ϊ�գ����ҽ��䷵�ظ�ʵ���ĵ����ߡ� Ȼ�������ȡ������ָ�������δ�����ĵ�����
	
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

//���԰������ⲻ��ֻ������Ψһʵ���������������Ƿ񴴽���ȷ
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

//����������ʽ������ֻ����Ҫʱ��ȡΨһʵ��

//����ʽ����ģʽ ��һ��ʼ�ʹ������̰߳�ȫ
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
		//��ȡ���ݿ����ݵĲ���������򵥶��������������
	}
	~HungrySingleton() {
		cout << "������������" << endl;
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
	
	//�þ�̬������ȡ
	// SingletonRecordFinder rf(SingletonDatabase::get()); //�ò���del
	//���˫�������� ��del��ֹ�ڴ�й©��˫�����������⣬������
	SingletonRecordFinder rf(*SingletonDatabase::get1()); // get1() ������ʵ����ͨ�����캯������ʼ��rf
	vector<string> names{ "alpha","beta" };
	int tp = rf.total_population(names);
	cout << tp << endl;;
	SingletonDatabase::del();

	SingletonRecordFinder rf1(HungrySingleton::get());
	cout << rf1.total_population(names) << endl;
	//HungrySingleton::del();
	
	
}