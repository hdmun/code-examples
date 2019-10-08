#include <iostream>


enum class eColor
{
	Red,
	Green = 1,
	Blue
};


int main()
{
	eColor color = eColor::Red;
	std::cout << "sizeof( eColor ): " << sizeof( eColor ) << std::endl;
	std::cout << "sizeof( color ): " << sizeof( color ) << std::endl;
}
