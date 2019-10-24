#include "StackWalk.h"

namespace dbghelp_dll {

func::SymInitializeProc _SymInitialize;
func::SymSetOptionsProc _SymSetOptions;
func::SymCleanUpProc _SymCleanUp;
func::StackWalkProc _StackWalk;
func::SymFunctionTableAccessProc _SymFunctionTableAccess;
func::SymGetModuleBaseProc _SymGetModuleBase;
func::SymGetSymFromAddrProc _SymGetSymFromAddr;
func::SymGetLineFromAddrProc _SymGetLineFromAddr;

HANDLE g_hProcess;


bool LoadDLLFunctions( HMODULE hDbgHelp )
{
	if ( !hDbgHelp ) {
		std::cout << "failed LoadLibrary `dbghelp.dll`" << std::endl;
		return false;
	}

#define _GetProcAddress( FUNCNAME, TYPE ) \
		_##FUNCNAME = reinterpret_cast<TYPE>( \
			::GetProcAddress( hDbgHelp, #FUNCNAME ) )

	_SymInitialize = _GetProcAddress( SymInitialize, func::SymInitializeProc );
	_SymCleanUp = _GetProcAddress( SymCleanUp, func::SymCleanUpProc );

	_StackWalk = _GetProcAddress( StackWalk, func::StackWalkProc );

	_SymFunctionTableAccess = _GetProcAddress( SymFunctionTableAccess, func::SymFunctionTableAccessProc );
	_SymGetModuleBase = _GetProcAddress( SymGetModuleBase, func::SymGetModuleBaseProc );
	_SymGetSymFromAddr = _GetProcAddress( SymGetSymFromAddr, func::SymGetSymFromAddrProc );
	_SymGetLineFromAddr = _GetProcAddress( SymGetLineFromAddr, func::SymGetLineFromAddrProc );
#undef _GetProcAddress

	return true;
}

bool Initialize()
{
	HMODULE hDbgHelp = ::LoadLibrary( TEXT( "dbghelp.dll" ) );
	if ( !LoadDLLFunctions( hDbgHelp ) ) {
		return false;
	}

	TCHAR sModule[MAX_PATH] = TEXT( "" );
	LPTSTR s = sModule + ::GetModuleFileName( 0, sModule, MAX_PATH ) - 1;

	while ( s >= sModule
		&& *s != TEXT( '/' )
		&& *s != TEXT( '\\' ) )
	{
		--s;
	}
	*(s + 1) = TEXT( '\0' );

	g_hProcess = ::GetCurrentProcess();
	if ( !_SymInitialize( g_hProcess, s, TRUE ) ) {
		return false;
	}

	_SymSetOptions = reinterpret_cast<func::SymSetOptionsProc>(
		::GetProcAddress( hDbgHelp, "SymSetOptions" )
		);
	if ( _SymSetOptions ) {
		_SymSetOptions(
			SYMOPT_CASE_INSENSITIVE | SYMOPT_UNDNAME
			| SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES
		);
	}

	return true;
}

}  // end of namespace dbghelp_dll

void IntelStackWalk( PCONTEXT pContext )
{
#ifndef _WIN64
	::printf_s( "\r\nCall stack:\r\n" );
	::printf_s( "Address   Frame     Logical addr  Module\r\n" );
	if ( !pContext ) {
		::printf_s( "Context is NULL\r\n" );
		return;
	}

	DWORD pc = pContext->Eip;
	LPDWORD pFrame, pPrevFrame;

	pFrame = reinterpret_cast<PDWORD>(pContext->Ebp);

	while ( true ) {

		TCHAR sModule[MAX_PATH] = TEXT( "" );
		DWORD dwSection = 0, dwOffset = 0;
		TCHAR sBuff128[128] = TEXT( "" );
		BOOL bRet = GetLogicalAddress( reinterpret_cast<LPVOID>(pc),
			sModule, sizeof( sModule ), dwSection, dwOffset, sBuff128 );
		::printf_s( "%08X  %08X  %04X:%08X %s",
			pc, pFrame, dwSection, dwOffset, sModule );
		if ( !bRet ) {
			::printf_s( " ErrorInfo : %s", sBuff128 );
		}
		::printf_s( "\r\n" );

		pc = pFrame[1];

		pPrevFrame = pFrame;

		// ���� ���������� �̵�
		pFrame = reinterpret_cast<LPDWORD>(pFrame[0]);

		// DWORD ��迡 ���� ������ ���� �߸��� ���̴�
		if ( reinterpret_cast<DWORD>(pFrame) & 3 ) break;
		// �� �������� ���� �����Ӻ��� ���� �󿡼� ������ �־�� �Ѵ�
		if ( pFrame <= pPrevFrame ) break;
		// �� �����ӿ��� ��� �� ���� DWORD �� ���� �� �־�� �Ѵ�
		if ( ::IsBadWritePtr( pFrame, sizeof( DWORD ) * 2 ) )
			break;
	}
#endif
}

LPCTSTR GetExceptionCodeStr( DWORD dwExceptioinCode )
{
#define __EXCEPTION_CASE( x ) case EXCEPTION_##x: return TEXT(#x)

	switch ( dwExceptioinCode )
	{
		__EXCEPTION_CASE( ACCESS_VIOLATION );
		__EXCEPTION_CASE( DATATYPE_MISALIGNMENT );
		__EXCEPTION_CASE( BREAKPOINT );
		__EXCEPTION_CASE( SINGLE_STEP );
		__EXCEPTION_CASE( ARRAY_BOUNDS_EXCEEDED );
		__EXCEPTION_CASE( FLT_DENORMAL_OPERAND );
		__EXCEPTION_CASE( FLT_DIVIDE_BY_ZERO );
		__EXCEPTION_CASE( FLT_INEXACT_RESULT );
		__EXCEPTION_CASE( FLT_INVALID_OPERATION );
		__EXCEPTION_CASE( FLT_OVERFLOW );
		__EXCEPTION_CASE( FLT_STACK_CHECK );
		__EXCEPTION_CASE( FLT_UNDERFLOW );
		__EXCEPTION_CASE( INT_DIVIDE_BY_ZERO );
		__EXCEPTION_CASE( INT_OVERFLOW );
		__EXCEPTION_CASE( PRIV_INSTRUCTION );
		__EXCEPTION_CASE( IN_PAGE_ERROR );
		__EXCEPTION_CASE( ILLEGAL_INSTRUCTION );
		__EXCEPTION_CASE( NONCONTINUABLE_EXCEPTION );
		__EXCEPTION_CASE( STACK_OVERFLOW );
		__EXCEPTION_CASE( INVALID_DISPOSITION );
		__EXCEPTION_CASE( GUARD_PAGE );
		__EXCEPTION_CASE( INVALID_HANDLE );
	}
#undef __EXCEPTION_CASE

	static TCHAR szBuffer[128] = { 0 };
	::FormatMessage( FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
		::GetModuleHandle( TEXT( "NTDLL.DLL" ) ), dwExceptioinCode, 0, szBuffer, sizeof( szBuffer ), 0 );

	return szBuffer;
}


BOOL GetLogicalAddress(
	LPVOID pAddr, LPTSTR sModule, DWORD len,
	DWORD& dwSection, DWORD& dwOffset, LPTSTR sBuff128 )
{
	MEMORY_BASIC_INFORMATION mbi = { 0, };
	if ( !::VirtualQuery( pAddr, &mbi, sizeof( mbi ) ) ) {
		::wsprintf( sBuff128, TEXT( "VirtualQuery failed" ) );
		return FALSE;
	}

	LPVOID hMod = mbi.AllocationBase;
	if ( !::GetModuleFileName( reinterpret_cast<HMODULE>(hMod), sModule, len ) ) {
		::wsprintf( sBuff128, TEXT( "GetModuleFileName failed" ) );
		return FALSE;
	}

	// DOS ��� ������
	PIMAGE_DOS_HEADER pDosHdr = reinterpret_cast<PIMAGE_DOS_HEADER>(hMod);
	if ( !pDosHdr ) {
		::wsprintf( sBuff128, TEXT( "DosHdr is NULL" ) );
		return FALSE;
	}

	// DOS ������� NT ����� ã�´�
	PIMAGE_NT_HEADERS pNtHdr = reinterpret_cast<PIMAGE_NT_HEADERS>(
		reinterpret_cast<LPBYTE>(hMod) + pDosHdr->e_lfanew);
	if ( !pNtHdr ) {
		::wsprintf( sBuff128, TEXT( "NtHdr is NULL" ) );
		return FALSE;
	}

	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );
	if ( !pSection ) {
		::wsprintf( sBuff128, TEXT( "Section is NULL" ) );
		return FALSE;
	}

	// ����� �ε�� �ּҿ����� �ɼ��� ����Ѵ�
	DWORD dwRva = static_cast<LPBYTE>(pAddr) - static_cast<LPBYTE>(hMod);

	// ���� ���̺� ��Ʈ�� �߿��� �ɼ��� �����ϴ� ���� ã�� �����Ѵ�
	for ( unsigned i = 0; i < pNtHdr->FileHeader.NumberOfSections; ++i, ++pSection ) {

		DWORD dwSectionStart = pSection->VirtualAddress;
		DWORD dwSectionEnd = dwSectionStart
			+ max( pSection->SizeOfRawData, pSection->Misc.VirtualSize );

		if ( dwSectionStart <= dwRva && dwRva <= dwSectionEnd ) {
			// ã�Ҵ�
			dwSection = i + 1;
			dwOffset = dwRva - dwSectionStart;
			return TRUE;
		}
	}

	::wsprintf( sBuff128, TEXT( "Can't Find Section" ) );
	return FALSE;
}
