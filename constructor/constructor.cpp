#include <iostream>


class Foo
{
public:
	Foo() {
		std::cout << "Foo()" << std::endl;
	}
	virtual ~Foo() {
		std::cout << "~Foo()" << std::endl;
	}

	operator bool() { return true; }
};


int main()
{
	if ( auto f = Foo() ) {
		std::cout << "inside if ( Foo() ) block" << std::endl;
	}

	std::cout << "end of main" << std::endl;
	return 0;
}
