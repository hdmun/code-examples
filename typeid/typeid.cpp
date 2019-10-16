#include <iostream>

class foo
{
public:
	const char* class_name() { return typeid( this ).name(); }
};

int main()
{
	foo foo;
	const char* name = foo.class_name();
	std::cout << name << std::endl;
}
