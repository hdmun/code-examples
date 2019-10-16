#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <tchar.h>

int main()
{
	std::cout << "NamedPipeServer" << std::endl;

	constexpr LPCTSTR lpName = TEXT( "\\\\.\\pipe\\WzAdminStalker" );
	constexpr DWORD dwOpenMode = PIPE_ACCESS_DUPLEX;
	constexpr DWORD dwPipeMode = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
	constexpr DWORD nMaxInstances = 1;
	constexpr DWORD nOutBufferSize = 65536;
	constexpr DWORD nInBufferSize = nOutBufferSize;
	constexpr DWORD nDefaultTimeOut = 0;
	constexpr LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr;
	HANDLE hPipe = ::CreateNamedPipe(
		lpName
		, dwOpenMode
		, dwPipeMode
		, nMaxInstances
		, nOutBufferSize
		, nInBufferSize
		, nDefaultTimeOut
		, lpSecurityAttributes
	);
	std::cout << "hPipe " << hPipe << std::endl;
	if ( hPipe == INVALID_HANDLE_VALUE ) {
		system( "pause" );
		return 1;
	}

	BOOL bConnect = ::ConnectNamedPipe( hPipe, nullptr );
	std::cout << "bConnect " << bConnect << std::endl;
	if ( !bConnect ) {
		system( "pause" );
		return 1;
	}

	while ( true ) {
		TCHAR recv[ MAX_PATH ] = { 0, };
		DWORD dwRecvSize = 0;
		BOOL bRead = ::ReadFile(
			hPipe
			, recv
			, MAX_PATH * sizeof( TCHAR )
			, &dwRecvSize
			, NULL );

		if ( !bRead || dwRecvSize == 0 ) {
			::Sleep( 100 );
			continue;
		}

		std::cout << "dwRecvSize " << dwRecvSize << std::endl;

		recv[ dwRecvSize / sizeof( TCHAR ) - 1 ] = TEXT( '\x00' );
		_tprintf( TEXT( "Recv Message : %s \n" ), recv );
	}

	::CloseHandle( hPipe );
	return 0;
}
