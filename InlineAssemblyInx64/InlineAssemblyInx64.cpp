// InlineAssemblyInx64.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <cstdio>

extern "C" int DivInt64( __int64 dividend, __int64 divider );

int main()
{
	int a = 0;
#if _M_AMD64
	a = DivInt64( 1111111111, 100 );
#else
	_asm
	{
		mov edx, 0
		mov eax, 1111111111
		mov ebx, 100
		div ebx

		mov a, eax
	}
#endif

	printf( "%d\n", a );
	printf( "%d\n", 1111111111 / 100 );
}
