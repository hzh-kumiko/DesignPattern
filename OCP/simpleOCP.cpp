#include<iostream>
#include<vector>
#include<string>
#include<fstream>

//开闭原则
//对扩展开放
//对修改关闭
//过滤器中根据过滤要求增加接口函数
enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
	std::string name;
	Color color;
	Size size;
	Product(std::string name_, Color color_, Size size_) :name(name_), color(color_), size(size_) {}
};

template <typename T>
struct Specification {
	virtual bool is_satisfied(T* item) = 0;
	
};

template <typename T>
struct Filter {
	virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) const = 0;
};

struct BetterFilter : Filter<Product> {
	std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) const override{
		std::vector<Product*> result;
		for (auto& i : items) {
			if (spec.is_satisfied(i)) {
				result.push_back(i);
			}
		}
		return result;
	}
};

struct ColorSpecification :Specification<Product> {
	Color color;
	explicit ColorSpecification(const Color color_) :color(color_) {}
	bool is_satisfied(Product* item) override {
		return item->color == color;
	}
};

struct SizeSpecification :Specification<Product> {
	Size size;
	explicit SizeSpecification(const Size size_) :size(size_) {}
	bool is_satisfied(Product* item) override {
		return item->size == size;
	}
};

struct ColorAndSizeSpecification :Specification<Product> {
	Specification<Product>& ColorSpec;
	Specification<Product>& SizeSpec;
	ColorAndSizeSpecification(Specification<Product>& spec1, Specification<Product>& spec2) :ColorSpec(spec1), SizeSpec(spec2) {}
	bool is_satisfied(Product* item) override {
		return ColorSpec.is_satisfied(item) && SizeSpec.is_satisfied(item);
	}
};
ColorAndSizeSpecification operator&& (Specification<Product>& spec1, Specification<Product>& spec2) {
	return { spec1,spec2 };
}

int main() {
	Product apple("Apple", Color::Red, Size::Small);
	Product tree("Tree", Color::Green, Size::Medium);
	Product tree1("Tree1", Color::Green, Size::Large);
	Product sky("Sky", Color::Blue, Size::Large);
	std::vector<Product*> list = { &apple,&tree,&sky,&tree1 };
	BetterFilter bf;
	ColorSpecification green(Color::Green);
	SizeSpecification large(Size::Large);
	//ColorAndSizeSpecification total(green, large);
	ColorAndSizeSpecification total = green && large;
	auto green_list = bf.filter(list, total);
	for (auto& l : green_list) {
		std::cout << l->name << std::endl;
	}
}