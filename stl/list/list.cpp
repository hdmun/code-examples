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

namespace _move {
void to_another_list()
{
	std::list<foo> list_;
	for ( int i = 0; i < 10; i++ )
		list_.push_back( foo() );

	std::cout << "print `list_` before move" << std::endl;
	for ( auto& elem : list_ )
		std::cout << "list_: " << &elem << ", " << elem.member << std::endl;

	std::list<foo> list_move_ = std::move( list_ );

	std::cout << "print `list_move_` after move" << std::endl;
	for ( auto& elem : list_move_ )
		std::cout << "list_move_: " << &elem << ", " << elem.member << std::endl;

	std::cout << "print `list_` after move" << std::endl;
	for ( auto& elem : list_ )
		std::cout << "list_: " << &elem << ", " << elem.member << std::endl;
}

void add_to_another_list()
{
	std::cout << std::endl << __FUNCTION__ << std::endl;

	std::list<foo> list_;
	for ( int i = 0; i < 10; i++ )
		list_.push_back( foo() );

	std::cout << "print `list_` before move" << std::endl;
	for ( auto& elem : list_ )
		std::cout << "list_: " << &elem << ", " << elem.member << std::endl;

	std::list<foo> list_move_;
	std::copy( list_.begin(), list_.end(), std::back_inserter( list_move_ ) );
	for ( auto& iter : list_move_ ) {
		iter.member += 100;
	}

	std::cout << "print `list_` after copy" << std::endl;
	for ( auto& elem : list_ )
		std::cout << "list_: " << &elem << ", " << elem.member << std::endl;

	// 흠 move 가 안먹히는군
	list_move_.insert( list_move_.begin(),
		std::make_move_iterator( list_.begin() ),
		std::make_move_iterator( list_.end() ) );

	std::cout << "print `list_move_` after insert move" << std::endl;
	for ( auto& elem : list_move_ )
		std::cout << "list_move_: " << &elem << ", " << elem.member << std::endl;

	std::cout << "print `list_` after insert move" << std::endl;
	for ( auto& elem : list_ )
		std::cout << "list_: " << &elem << ", " << elem.member << std::endl;

}

}

int main()
{
	// store_list_iter();
	//_move::to_another_list();
	_move::add_to_another_list();
}
