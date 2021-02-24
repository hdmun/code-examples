#include <iostream>
#include <memory>
#include <map>

struct Foo
{
    Foo() = default;
    // Foo() {
    //     std::cout << "Foo::Foo() member: " << std::endl;
    //     std::cout << this->mMap.size() << std::endl;
    //     std::cout << this->member << std::endl;
    //     std::cout << this->bBoolean << std::endl;
    // }
	virtual ~Foo() {
		std::cout << "Foo::~Foo(): " << std::endl;
		std::cout << this->mMap.size() << std::endl;
		std::cout << this->member << std::endl;
		std::cout << this->bBoolean << std::endl;
        std::cout << std::endl;
	}

    std::map<int, int> mMap;
    int member{ 1 };
    bool bBoolean{ false };
};

void test_get_scope()
{
	Foo* pFoo = nullptr;
	{
		std::unique_ptr<Foo> ufoo = std::make_unique<Foo>();
		std::cout << ufoo.get() << std::endl;
		pFoo = ufoo.get();
	}

	std::cout << "Out Scope " << std::endl;
	std::cout << pFoo << std::endl;
	std::cout << pFoo->mMap.size() << std::endl;
	std::cout << pFoo->member << std::endl;
	std::cout << pFoo->bBoolean << std::endl;
}

int main()
{
	// test_get_scope();
}
