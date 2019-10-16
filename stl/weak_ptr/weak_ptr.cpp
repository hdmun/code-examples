#include <iostream>
#include <atomic>
#include <memory>


std::atomic<int> g_key = 0;


struct client_socket
{
	client_socket() : key( ++g_key ){}

	int key{ 0 };
};


int main()
{
	std::shared_ptr<client_socket> sp = std::make_shared<client_socket>();
	std::cout << "sp.key: " << sp->key << std::endl;

	std::weak_ptr<client_socket> wp = sp;
	std::cout << "wp.expired(): " << wp.expired() << std::endl;
	{
		std::shared_ptr<client_socket> sp_local = wp.lock();
		std::cout << "sp_local.key: " << sp_local->key << std::endl;
	}

	std::cout << "wp.lock()->key: " << wp.lock()->key << std::endl;
}
