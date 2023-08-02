#include <iostream>
#include <string>

template <typename T>
concept ComplexConcept =
!std::has_virtual_destructor<T>::value && 
	requires(T v) {
		{ v.hash() } -> std::convertible_to<long>; 
		{ v.toString() } -> std::same_as<std::string>; 
};

void PrintType(ComplexConcept auto& t) {
	std::cout << "Type is correct.\n";
	std::cout << "toString method - Hash is " << t.toString() << "\n";
	std::cout << "hash method - Hash is " << t.hash() << "\n";
}


class CorrectTestClass
{
public:
	CorrectTestClass(const std::string& hash) : _hash(hash) {}; 
	~CorrectTestClass() {};
	size_t hash() { return std::hash<std::string> {} (_hash); } 
	std::string toString() const { return _hash; }

private:
	std::string _hash;
};


class IncorrectTestClass
{
public:
	IncorrectTestClass(const std::string& hash) : _hash(hash) {}; 
	virtual ~IncorrectTestClass() {}; 
	size_t hash() { return std::hash<std::string> {} (_hash); } 
	int toInt(int a, int b) {
		return a + b;
	}
	
private:
	std::string _hash;
};


int main()
{
	CorrectTestClass a{ "Hello" };
	IncorrectTestClass b{ "password1234" };

	PrintType(a);
	PrintType(b);

	return 0;
}
