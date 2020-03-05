// CheckRemote.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


BOOL IsRemoteSession( void )
{
	return GetSystemMetrics( SM_REMOTESESSION );
}

BOOL IsRemoteControl( void )
{
	return GetSystemMetrics( SM_REMOTECONTROL );
}

int main()
{
	while ( true ) {
		std::cout << "IsRemoteSession: " << IsRemoteSession();
		std::cout << ", IsRemoteControl: " << IsRemoteControl();
		std::cout << std::endl;
		Sleep( 1000 );
	}

	return 0;
}
