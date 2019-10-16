#include <Windows.h>
#include <cassert>
#include <tchar.h>
#include <iostream>


int main()
{
	HWND hWnd = ::FindWindow( nullptr, TEXT( "WzStalkerMonitor_Host" ) );
	assert( hWnd );

	auto msg = TEXT( "Message From Another Process" );
	::PostMessage( hWnd, WM_USER+1, 0, reinterpret_cast<LPARAM>( msg ) );

	COPYDATASTRUCT cds;
	cds.dwData = 1;
	cds.cbData = sizeof( TCHAR ) * ( _tcslen( msg ) + 1 );
	cds.lpData = (void*)msg;
	::PostMessage( hWnd, WM_COPYDATA, reinterpret_cast<WPARAM>( hWnd ), reinterpret_cast<LPARAM>( &cds ) );
	return 0;
}
