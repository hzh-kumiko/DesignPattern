#include<iostream>
#include<vector>
#include<string>
#include<fstream>

//单一职责
//一个类用来做一个任务
//Journal用来维护日志
//存储由另一个类实现
struct Journal {
	std::string title;
	std::vector<std::string> entries;
	Journal(std::string title_) :title(title_) {};
	void add(const std::string& entry);
	void show();
};
struct Persistence {
	static void save(Journal j, const std::string& filename);
};
void Journal::add(const std::string& entry) {
	static int index = 1;
	entries.push_back(std::to_string(index++) + ":" + entry);
	
}

void Journal::show() {
	std::cout << "The record of" << title << std::endl;
	for (auto& e : entries) {
		std::cout << e << std::endl;
	}
}
void Persistence::save(Journal j, const std::string& filename)
{
	std::ofstream of(filename, std::ios::app);
	for (auto& e : j.entries) {
		of << e << std::endl;
	}
}
int main() {
	Journal j1("Dear M"), j2("Dear H");
	
	j1.add("first entry");
	j2.add("second entry");
	j1.show();
	j2.show();
	std::string path = "E:\\DesignPatterns\\principle\\text.txt";
	Persistence p;
	p.save(j1, path);
	p.save(j2, path);
}