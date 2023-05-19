#include<iostream>
#include<map>
#include<vector>
#include<memory>
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
class Database {
public:
	virtual int get_population(const string& name) = 0;
	~Database() {
		cout << "xigou" << endl;
	}
};

class SingletonDatabase :public Database {
private:
	SingletonDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
	}
	map<string, int> capitals;
public:
	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;
	static SingletonDatabase& get() {
		static SingletonDatabase db;
		return db;
	}
	/*static SingletonDatabase& get() {
		static shared_ptr<SingletonDatabase> db(new SingletonDatabase);
		return *db;
	}*/
	int get_population(const string& name) {
		return capitals[name];
	}

};

class SingletonRecordFinder {
public:
	explicit SingletonRecordFinder(Database& db_):db(db_){
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
int main() {
	//Database *db = &SingletonDatabase::get();
	
	SingletonRecordFinder rf(SingletonDatabase::get());
	vector<string> names{ "alpha","beta" };
	int tp = rf.total_population(names);
	cout << tp;
}