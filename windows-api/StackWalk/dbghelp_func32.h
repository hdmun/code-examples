#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <DbgHelp.h>
#include <cstdio>

namespace dbghelp_dll {
namespace func {

#ifndef _WIN64

typedef BOOL( WINAPI* SymInitializeProc )(HANDLE, PCWSTR, BOOL);
typedef BOOL( WINAPI* SymSetOptionsProc )(DWORD);
typedef BOOL( WINAPI* SymCleanUpProc )(HANDLE);

typedef BOOL( WINAPI* StackWalkProc )
(DWORD, HANDLE, HANDLE, LPSTACKFRAME, LPVOID,
	PREAD_PROCESS_MEMORY_ROUTINE, PFUNCTION_TABLE_ACCESS_ROUTINE,
	PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE);

typedef LPVOID( WINAPI* SymFunctionTableAccessProc )(HANDLE, DWORD);
typedef DWORD( WINAPI* SymGetModuleBaseProc )(HANDLE, DWORD);
typedef BOOL( WINAPI* SymGetSymFromAddrProc ) (HANDLE, DWORD, PDWORD, PIMAGEHLP_SYMBOL);
typedef BOOL( WINAPI* SymGetLineFromAddrProc ) (HANDLE, DWORD, PDWORD, PIMAGEHLP_LINE);

#endif  // end of #ifndef _WIN64

#ifdef _M_IX86
void PrintRegister32( PCONTEXT pContext );
#endif
}  // end of namespace func
}  // end of namespace dbghelp_dll
