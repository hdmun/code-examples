#include <iostream>
#include <vector>

void push_back_after_reserve()
{
	std::vector<int> v;
	for ( int i = 0; i < 5; i++ ) {
		v.push_back( i );
	}

	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl;

	v.reserve( v.size() * 2 );

	for ( int i = 5; i < 10; i++ ) {
		v.push_back( i );
	}

	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl;
	for ( auto& iter : v ) {
		std::cout << iter << std::endl;
	}
}

int main()
{
	push_back_after_reserve();
}
