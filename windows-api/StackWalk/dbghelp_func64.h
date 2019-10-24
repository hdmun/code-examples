#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <DbgHelp.h>
#include <cstdio>

namespace dbghelp_dll {
namespace func {

#ifdef _WIN64

typedef BOOL( WINAPI* SymInitializeProc )(HANDLE, PCWSTR, BOOL);
typedef BOOL( WINAPI* SymSetOptionsProc )(DWORD);
typedef BOOL( WINAPI* SymCleanUpProc )(HANDLE);

typedef BOOL( WINAPI* StackWalkProc )
(DWORD64, HANDLE, HANDLE, LPSTACKFRAME, LPVOID,
	PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64,
	PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64);

typedef LPVOID( WINAPI* SymFunctionTableAccessProc )(HANDLE, DWORD64);
typedef DWORD64( WINAPI* SymGetModuleBaseProc )(HANDLE, DWORD64);
typedef BOOL( WINAPI* SymGetSymFromAddrProc ) (HANDLE, DWORD64, PDWORD64, PIMAGEHLP_SYMBOL64);
typedef BOOL( WINAPI* SymGetLineFromAddrProc ) (HANDLE, DWORD64, PDWORD64, PIMAGEHLP_LINE64);

#endif  // end of #ifdef _WIN64

#ifdef _M_X64
void PrintRegister64( PCONTEXT pContext );
#endif

}  // end of namespace func
}  // end of namespace dbghelp_dll
