#include <iostream>


enum class eColor
{
	Red,
	Green = 1,
	Blue
};

enum class eUint8 : unsigned char
{
	One,
	Two
};

enum class eUint64 : unsigned __int64
{
	One,
	Two
};


void print_sizeof()
{
	eColor color = eColor::Red;
	std::cout << "sizeof( eColor ): " << sizeof( eColor ) << std::endl;
	std::cout << "sizeof( color ): " << sizeof( color ) << std::endl;

	eUint8 euint8 = eUint8::One;
	std::cout << "sizeof( eUint8 ): " << sizeof( eUint8 ) << std::endl;
	std::cout << "sizeof( euint64 ): " << sizeof( euint8 ) << std::endl;

	eUint64 euint64 = eUint64::One;
	std::cout << "sizeof( eUint64 ): " << sizeof( eUint64 ) << std::endl;
	std::cout << "sizeof( euint64 ): " << sizeof( euint64 ) << std::endl;
}

int main()
{
	print_sizeof();
}
