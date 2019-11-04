#include <iostream>
#include <mutex>
#include <thread>


namespace custom_lock_guard {

template <class _Mutex>
class Lock
	: public std::lock_guard<_Mutex>
{
public:
	operator bool() { return true; }

	using mutex_type = _Mutex;

	Lock( _Mutex& _Mtx )
		: std::lock_guard< _Mutex >(_Mtx)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	Lock( _Mutex& _Mtx, std::adopt_lock_t )
		: std::lock_guard< _Mutex >( _Mtx )
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	virtual ~Lock() noexcept
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	Lock( const Lock& ) = delete;
	Lock& operator=( const Lock& ) = delete;
};

std::mutex lock_;

void run()
{
	std::thread thread1( [&]() {
			for ( int i = 0; i < 5; ++i )
			{
				if ( Lock<std::mutex> guard = lock_ ) {
					std::cout << "Thread Num : " << i << std::endl;
				}
			}
		} );

	std::thread thread2 = std::thread( [&]()
		{
			for ( int i = 10; i < 15; ++i )
			{
				if ( Lock<std::mutex> guard = lock_ ) {
					std::cout << "Thread Num : " << i << std::endl;
				}
			}
		} );

	std::thread thread3 = std::thread( [&]( int nParam )
		{
			for ( int i = 20; i < 25; ++i )
			{
				if ( Lock<std::mutex> guard = lock_ ) {
					std::cout << "Thread Parameter : " << nParam << std::endl;
				}
			}
		}, 4 );

	thread1.join();
	thread2.join();
	thread3.join();
}

}

int main()
{
	custom_lock_guard::run();

	std::cout << "end of main()" << std::endl;
	return 0;
}
