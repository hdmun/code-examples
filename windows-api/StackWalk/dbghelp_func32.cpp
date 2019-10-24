#include "dbghelp_func32.h"


namespace dbghelp_dll {
namespace func {

#ifdef _M_IX86
void PrintRegister32( PCONTEXT pContext )
{
	::printf_s( "\r\nRegisters:\r\n" );
	::printf_s( "EAX:%08X\r\nEBX:%08X\r\nECX:%08X\r\nEDX:%08X\r\nESI:%08X\r\nEDI:%08X\r\n",
		pContext->Eax, pContext->Ebx, pContext->Ecx, pContext->Edx, pContext->Esi, pContext->Edi );

	::printf_s( "CS:EIP:%04X:%08X\r\n", pContext->SegCs, pContext->Eip );
	::printf_s( "SS:ESP:%04X:%08X  EBP:%08X\r\n", pContext->SegSs, pContext->Esp, pContext->Ebp );
	::printf_s( "DS:%04X  ES:%04X  FS:%04X  GS:%04X\r\n", pContext->SegDs, pContext->SegEs, pContext->SegFs, pContext->SegGs );
	::printf_s( "Flags:%08X\r\n", pContext->EFlags );
}
#endif

}  // end of namespace func
}  // end of namespace dbghelp_dll
