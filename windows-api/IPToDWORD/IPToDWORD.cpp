#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <WS2tcpip.h>

#include <cstdio>


int main()
{
	const char* ip = "127.0.0.1";
	in_addr addr = { 0, };

	INT nRet = ::inet_pton( AF_INET, ip, &addr.s_addr );
	printf( "%lu\n", addr.s_addr );
}
