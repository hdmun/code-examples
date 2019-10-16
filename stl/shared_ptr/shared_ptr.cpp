#include <iostream>
#include <atomic>
#include <memory>


std::atomic<int> g_key = 0;


struct client_socket
{
	//client_socket() : key( ++g_key ) {}

	int key{ ++g_key };
};


void delete_first_shared_ptr()
{
	std::cout << __FUNCTION__ << std::endl;

	client_socket* rawp = new client_socket;
	std::cout << "rawp.key: " << rawp->key << std::endl;

	std::shared_ptr<client_socket> sp;// = std::make_shared<client_socket>( rawp );
	sp.reset( rawp );
	std::cout << "sp.key: " << sp->key << std::endl;

	rawp->key++;
	std::cout << "rawp.key: " << rawp->key << std::endl;
	std::cout << "sp.key: " << sp->key << std::endl;

	sp = nullptr;
	std::cout << "rawp.key: " << rawp->key << std::endl;
	std::cout << std::endl;
}


void delete_first_raw_pointer()
{
	std::cout << __FUNCTION__ << std::endl;

	client_socket* rawp = new client_socket;
	std::cout << "rawp.key: " << rawp->key << std::endl;

	std::shared_ptr<client_socket> sp;// = std::make_shared<client_socket>( rawp );
	sp.reset( rawp );
	std::cout << "sp.key: " << sp->key << std::endl;

	rawp->key++;
	std::cout << "rawp.key: " << rawp->key << std::endl;
	std::cout << "sp.key: " << sp->key << std::endl;

	delete rawp;
	std::cout << "sp.key: " << sp->key << std::endl;
	std::cout << std::endl;
}

class base
{
	int _base{ 0 };
};

class derived : public base
{
	int _derived{ 1 };
};

void up_cast()
{
	std::shared_ptr<derived> pDerived = std::make_shared<derived>();
	std::shared_ptr<base> pBase = pDerived;
}

namespace shared_ptr_this {
	class foo;
	void arg_to_this( std::shared_ptr<foo> fromthis );
	void arg_to_this_weak( std::weak_ptr<foo> fromthis );

	class foo : public std::enable_shared_from_this<foo>
	{
	public:
		int n{ ++g_key };

		void do_something()
		{
			arg_to_this( shared_from_this() );
			arg_to_this_weak( shared_from_this() );
		}
	};

	void run()
	{
		std::shared_ptr<foo> p = std::make_shared<foo>();
		p->do_something();
	}

	void arg_to_this( std::shared_ptr<foo> fromthis )
	{
	}

	void arg_to_this_weak( std::weak_ptr<foo> fromthis )
	{
		std::weak_ptr<foo> _assign = fromthis;
	}
}

int main()
{
	shared_ptr_this::run();
}
