#include <iostream>
#include <atomic>
#include <list>

#include <cassert>


std::atomic<int> g_key = 0;

struct foo
{
	int member{ ++g_key };
};


void store_list_iter()
{
	std::list<foo> list_;
	for ( int i = 0; i < 5; i++ ) {
		list_.push_back( foo() );
	}

	std::list<foo>::iterator it_store = list_.end();

	it_store--;
	std::cout << "list_.size: " << list_.size() << ", it_store->member: " << it_store->member << std::endl;

	list_.remove_if( []( auto& elem ) {
		return elem.member == 2;
	} );
	std::cout << "list_.size: " << list_.size() << ", it_store->member: " << it_store->member << std::endl;

	// 이러면 죽는다.
// 	list_.clear();
// 	assert( it_store == list_.end() );

	// 이래도 죽는다.
	list_.remove_if( [it_store]( auto& elem ) {
		return elem.member == it_store->member;
	} );
	std::cout << "list_.size: " << list_.size() << ", it_store->member: " << it_store->member << std::endl;
}


int main()
{
	store_list_iter();
}
