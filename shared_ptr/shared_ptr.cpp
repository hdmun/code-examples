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


int main()
{
	delete_first_shared_ptr();
	delete_first_raw_pointer();
}
