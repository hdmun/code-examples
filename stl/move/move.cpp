#include <iostream>
#include <list>


class foo {
public:
	foo() {
		std::cout << "foo()" << std::endl;
	}
	virtual ~foo() {
		std::cout << "~foo()" << std::endl;
	}
};


int main()
{
	std::list< std::unique_ptr< foo > > l1;
	l1.push_back( std::make_unique< foo >() );

	std::list< std::unique_ptr< foo > > l2;
	std::move( l1.begin(), l1.end(), std::move_backward( l2 ) );

	std::cout << "l1.size(): " << l1.size() << ", " << "l2.size(): " << l2.size() << std::endl;
	return 0;
}
