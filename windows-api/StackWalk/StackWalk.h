#pragma once

//////////////////////////////////////////////////////////////////////////
/// references
/// https://docs.polserver.com/doxygen/html/dc/dc4/msjexhnd_8cpp_source.html

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <DbgHelp.h>
#include <cstdio>
#include <iostream>

#ifdef _WIN64
#include "dbghelp_func64.h"
#else
#include "dbghelp_func32.h"
#endif // _WIN64


namespace dbghelp_dll {

extern func::SymInitializeProc _SymInitialize;
extern func::SymSetOptionsProc _SymSetOptions;
extern func::SymCleanUpProc _SymCleanUp;
extern func::StackWalkProc _StackWalk;
extern func::SymFunctionTableAccessProc _SymFunctionTableAccess;
extern func::SymGetModuleBaseProc _SymGetModuleBase;
extern func::SymGetSymFromAddrProc _SymGetSymFromAddr;
extern func::SymGetLineFromAddrProc _SymGetLineFromAddr;

extern HANDLE g_hProcess;

bool Initialize();

#ifdef _WIN64
void StackWalk64( PCONTEXT pContext );
#else
void StackWalk32( PCONTEXT pContext );
#endif // _WIN64

}  // end of namespace dbghelp_dll

void IntelStackWalk( PCONTEXT pContext );
LPCTSTR GetExceptionCodeStr( DWORD dwExceptioinCode );
BOOL GetLogicalAddress(
	LPVOID pAddr, LPTSTR sModule, DWORD len,
	DWORD& dwSection, DWORD& dwOffset, LPTSTR sBuff128 );
