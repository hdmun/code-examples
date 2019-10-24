#include "StackWalk.h"

namespace dbghelp_dll {

#ifdef _WIN64

void StackWalk64( PCONTEXT pContext )
{
	::printf_s( "\r\nCall stack:\r\n" );
	::printf_s( "Address   Frame\r\n" );
	if ( !pContext ) {
		::printf_s( "Context is NULL\r\n" );
		return;
	}

	STACKFRAME64 sf = { 0 };  // // 최초의 호출을 위해 초기화한다 ( 인텔에서만 필요함 )
	sf.AddrPC.Offset = pContext->Rip;
	sf.AddrPC.Mode = AddrModeFlat;
	sf.AddrStack.Offset = pContext->Rsp;
	sf.AddrStack.Mode = AddrModeFlat;
	sf.AddrFrame.Offset = pContext->Rbp;
	sf.AddrFrame.Mode = AddrModeFlat;

	while ( true ) {
		if ( !_StackWalk( IMAGE_FILE_MACHINE_AMD64,
			::GetCurrentProcess(), ::GetCurrentThread(), &sf,
			pContext, 0, _SymFunctionTableAccess, _SymGetModuleBase, 0 )
			|| !sf.AddrFrame.Offset ) {
			break;
		}

		::printf_s( "%016X  %016X  ", sf.AddrPC.Offset, sf.AddrFrame.Offset );

		// IMAGEHLP_SYMBOL 구조체는 가변 크기를 가진다
		BYTE abSymbolBuffer[sizeof( IMAGEHLP_SYMBOL ) + 512];
		PIMAGEHLP_SYMBOL pSymbol = reinterpret_cast<PIMAGEHLP_SYMBOL>(abSymbolBuffer);
		pSymbol->SizeOfStruct = sizeof( IMAGEHLP_SYMBOL );
		pSymbol->MaxNameLength = sizeof( abSymbolBuffer ) - sizeof( IMAGEHLP_SYMBOL );

		// 심볼 시작 주소에서 상대적인 입력 주소의 변위
		DWORD64 dwSymDisplacement = 0;
		TCHAR sModule[MAX_PATH] = TEXT( "" );
		DWORD dwSection = 0, dwOffset = 0;
		IMAGEHLP_LINE il = { sizeof( IMAGEHLP_LINE ) };
		il.LineNumber = ~0UL;

		BOOL bFound = _SymGetSymFromAddr( g_hProcess,
			sf.AddrPC.Offset, &dwSymDisplacement, pSymbol );

		if ( bFound && _SymGetLineFromAddr )
			_SymGetLineFromAddr( g_hProcess, sf.AddrPC.Offset,
				&dwSymDisplacement, &il );

		TCHAR sBuff128[128] = TEXT( "" );
		BOOL bRet = GetLogicalAddress( reinterpret_cast<LPVOID>(sf.AddrPC.Offset), sModule, sizeof( sModule ), dwSection, dwOffset, sBuff128 );
		if ( il.LineNumber != ~0UL )
			::printf_s( "%hs() %hs(%lu) [%s]", pSymbol->Name, il.FileName, il.LineNumber, sModule );
		else if ( bFound )
			::printf_s( "%hs()+%X [%s]", pSymbol->Name, dwSymDisplacement, sModule );
		else // 심볼이 없으면 주소를 출력한다
			::printf_s( "%016X:%016X [%s]", dwSection, dwOffset, sModule );
		if ( !bRet ) {
			::printf_s( " ErrorInfo : %s", sBuff128 );
			}
		::printf_s( "\r\n" );
	}
}

#endif  // _WIN64

}  // end of namespace dbghelp_dll
