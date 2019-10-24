#include "dbghelp_func64.h"


namespace dbghelp_dll {
namespace func {

#ifdef _M_X64
void PrintRegister64( PCONTEXT pContext )
{
	::printf_s( "\r\nRegisters(x64):\r\n" );

	::printf_s( "EAX:%016X\r\nEBX:%016X\r\nECX:%016X\r\nEDX:%016X\r\nESI:%016X\r\nEDI:%016X\r\n",
		pContext->Rax, pContext->Rbx, pContext->Rcx, pContext->Rdx, pContext->Rsi, pContext->Rdi );

	::printf_s( "\r\nR8:%016X\r\nR9:%016X\r\nXMM0:%016X\r\nXMM1:%016X\r\nXMM2:%016X\r\nXMM3:%016X\r\n\r\n",
		pContext->R8, pContext->R9, pContext->Xmm0, pContext->Xmm1, pContext->Xmm2, pContext->Xmm3 );

	::printf_s( "CS:EIP:%04X:%016X\r\n", pContext->SegCs, pContext->Rip );
	::printf_s( "SS:ESP:%04X:%016X  EBP:%016X\r\n", pContext->SegSs, pContext->Rsp, pContext->Rbp );
	::printf_s( "DS:%04X  ES:%04X  FS:%04X  GS:%04X\r\n", pContext->SegDs, pContext->SegEs, pContext->SegFs, pContext->SegGs );
	::printf_s( "Flags:%08X\r\n", pContext->EFlags );
}
#endif

}  // end of namespace func
}  // end of namespace dbghelp_dll
