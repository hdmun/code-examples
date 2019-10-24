#include "StackWalk.h"


DWORD WINAPI UnhandledExceptionFunc( LPVOID lpThreadParameter )
{
	std::cout << __FUNCTION__ << std::endl;

	PEXCEPTION_POINTERS pExceptInfo = reinterpret_cast<PEXCEPTION_POINTERS>(lpThreadParameter);

	// 시각을 찍는다
	SYSTEMTIME st = { 0, };
	::GetLocalTime( &st );
	::printf_s( "==== %d/%d/%d %02d:%02d:%02d.%03d ==============================\r\n",
		st.wYear, st.wMonth, st.wDay,
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );

	::printf_s( "PID(%X), TID(%X)\r\n", ::GetCurrentProcessId(), ::GetCurrentThreadId() );

	// pExceptionInfo
#ifdef _M_IX86
	::printf_s( "ExceptionInfo Address:  %08X\r\n", pExceptInfo );
#elif _M_X64
	::printf_s( "ExceptionInfo Address:  %016X\r\n", pExceptInfo );
#endif

	PEXCEPTION_RECORD pRecord = pExceptInfo ? pExceptInfo->ExceptionRecord : NULL;
	if ( pRecord ) {
		DWORD dwExceptionCode = pRecord->ExceptionCode;
		::printf_s( "Exception code: %08X %s", dwExceptionCode, GetExceptionCodeStr( dwExceptionCode ) );

		PVOID pExceptionAddress = pRecord->ExceptionAddress;
#ifdef _M_IX86
		::printf_s( "\r\nFault Address:  %08X", pExceptionAddress );
#elif _M_X64
		::printf_s( "\r\nFault Address:  %016X", pExceptionAddress );
#endif

		// 예외 위치 출력
		::printf_s( "\r\nFault Address:  " );
		TCHAR sModule[MAX_PATH] = TEXT( "" );
		DWORD dwSection = 0;
		DWORD dwOffset = 0;
		TCHAR sBuff128[128] = TEXT( "" );
		BOOL bRet = GetLogicalAddress( pExceptionAddress, sModule, sizeof( sModule ), dwSection, dwOffset, sBuff128 );
#ifdef _M_IX86
		::printf_s( "%08X %02X:%08X\r\nModule: %s", pExceptionAddress, dwSection, dwOffset, sModule );
#elif _M_X64
		::printf_s( "%016X %02X:%08X\r\nModule: %s", pExceptionAddress, dwSection, dwOffset, sModule );
#endif
		if ( !bRet ) {
			::printf_s( " ErrorInfo : %s", sBuff128 );
		}
		::printf_s( "\r\n" );
	}

	PCONTEXT pContext = pExceptInfo ? pExceptInfo->ContextRecord : NULL;
	if ( pContext ) {
#ifdef _M_IX86
		dbghelp_dll::func::PrintRegister32( pContext );
#elif _M_X64
		dbghelp_dll::func::PrintRegister64( pContext );
#endif
	}

	// IntelStackWalk( pContext );

#ifdef _WIN64
	dbghelp_dll::StackWalk64( pContext );
#else
	dbghelp_dll::StackWalk32( pContext );
#endif // _WIN64

	::printf_s( "\r\n" );
	return 0;
}

LONG WINAPI RawUnhandledExceptionFilter( PEXCEPTION_POINTERS pExceptionInfo )
{
	return UnhandledExceptionFunc( pExceptionInfo );
}

void Crash()
{
	volatile int a[10] = { 0, };
	a[9999] = 0;
}

namespace call_depth
{
void done( PCONTEXT pContext, int i, bool crash )
{
	if ( crash ) {
		Crash();
		return;
	}

	CONTEXT ctx = { 0, };
	ctx.ContextFlags = CONTEXT_ALL;
	::RtlCaptureContext( &ctx );
#ifdef _WIN64
	dbghelp_dll::StackWalk64( &ctx );
#else
	dbghelp_dll::StackWalk32( &ctx );
#endif // _WIN64
}

void call5( PCONTEXT pContext, volatile int i, bool crash ) { done( pContext, i+1 % i++, crash ); }
void call4( PCONTEXT pContext, volatile int i, bool crash ) { call5( pContext, i+1 % i++, crash ); }
void call3( PCONTEXT pContext, volatile int i, bool crash ) { call4( pContext, i+1 % i++, crash ); }
void call2( PCONTEXT pContext, volatile int i, bool crash ) { call3( pContext, i+1 % i++, crash ); }
void call1( PCONTEXT pContext, volatile int i, bool crash ) { call2( pContext, i+1 % i++, crash ); }
void start( PCONTEXT pContext, volatile int i, bool crash ) { call1( pContext, i+1 % i++, crash ); }

}  // end of namespace runtime_callstack

int main()
{
	dbghelp_dll::Initialize();
	::SetUnhandledExceptionFilter( RawUnhandledExceptionFilter );

	// Crash();

	CONTEXT ctx = { 0, };
	ctx.ContextFlags = CONTEXT_ALL;
	::RtlCaptureContext( &ctx );

	call_depth::start( &ctx, 50, false );

	return 0;
}
