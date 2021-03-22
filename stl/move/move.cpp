#include <iostream>
#include <list>

static int g_id = 1;

class foo {
public:
	foo() {
		std::cout << "foo()" << std::endl;
	}
	virtual ~foo() {
		std::cout << "~foo()" << std::endl;
	}

	int id{ g_id++ };
};

void test_move_list_unique_ptr()
{
	std::list< std::unique_ptr< foo > > l1;
	for (int i = 0; i < 5; i++) {
		l1.push_back(std::make_unique< foo >());
	}

	std::list< std::unique_ptr< foo > > l2;
	// std::move(l1.begin(), l1.end(), std::move_backward(l2));

	std::cout << "test_move_list_unique_ptr: l1.size(): " << l1.size() << ", " << "l2.size(): " << l2.size() << std::endl;
}

void test_move_struct_to_list()
{
	std::cout << __FUNCTION__ << std::endl;

	foo foo1;

	std::list<foo> l1 = { foo() };
	l1.push_back(std::move(foo1));
	for (auto& e : l1) {
		std::cout << e.id << std::endl;
	}

	std::cout << foo1.id << std::endl;
}

int main()
{
	// test_move_list_unique_ptr();
	test_move_struct_to_list();
	return 0;
}
