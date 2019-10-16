#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>

int main()
{
	std::cout << "NamedPipeClient" << std::endl;

	HANDLE hPipe = ::CreateFile(
		TEXT( "\\\\.\\pipe\\WzAdminStalker" )
		, GENERIC_READ | GENERIC_WRITE
		, 0
		, NULL
		, OPEN_EXISTING
		, 0
		, NULL
	);
	std::cout << "hPipe " << hPipe << std::endl;
	if ( hPipe == INVALID_HANDLE_VALUE ) {
		system( "pause" );
		return 1;
	}

	DWORD dwMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL bRet = ::SetNamedPipeHandleState( hPipe, &dwMode, NULL, NULL );
	std::cout << "bRet " << bRet << std::endl;
	if ( !bRet ) {
		system( "pause" );
		return 1;
	}

	TCHAR message[ MAX_PATH ] = TEXT("Message from Client");
	DWORD dwSendSize = 0;
	while ( true ) {
		BOOL bWrite = ::WriteFile(
			hPipe
			, message
			, MAX_PATH * sizeof( TCHAR )
			, &dwSendSize
			, NULL
		);
		if ( !bWrite || dwSendSize == 0 ) {
			::Sleep( 100 );
			continue;
		}

		std::cout << "bWrite " << bWrite << ", dwSendSize " << dwSendSize << std::endl;
	}

	::CloseHandle( hPipe );
	return 0;
}
