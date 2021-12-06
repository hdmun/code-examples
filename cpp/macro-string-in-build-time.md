# include 파일명 매크로 전처리기를 사용해 문자열 조합하기

#C++매크로 #C++Macro #cpp문자열조합 #c++includeMacro

뻘짓으로 시도해본 c++ `#include` 파일명을 매크로 전처리로 다르게 처리하기

~~~cpp
#ifdef _WIN64
#define __PLATFORM x64
#else
#define __PLATFORM Win32
#endif

#ifdef _DEBUG
#define __BUILD Debug
#else
#define __BUILD Release
#endif

#define __STRINGIFY_(filename) #filename
#define __STRINGIFY(_macro) __STRINGIFY_(_macro)
#define __CONCAT_(x, y) x ## y
#define __CONCAT(x, y) __CONCAT_(x, y)
#define __CONCAT_SEP(x, y) __CONCAT(x, __CONCAT(_, y))
#define __BUILD_PLATFORM __CONCAT_SEP(__BUILD, __PLATFORM)

#include __STRINGIFY( __CONCAT_SEP( HeaderFileName, __CONCAT( __BUILD_PLATFORM, .h ) ) )

// 조합 예시
// #include HeaderFileName_x64_Debug.h
// #include HeaderFileName_Win32_Debug.h
// #include HeaderFileName_x64_Release.h
// #include HeaderFileName_Win32_Release.h
~~~
