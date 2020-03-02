#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>


HKEY _RegCreateKeyExW()
{
	LPCWSTR lpSubKey = L"SOFTWARE\RegTest";
	DWORD Reserved = 0;
	LPWSTR lpClass = nullptr;
	DWORD dwOption = REG_OPTION_NON_VOLATILE;
	static const REGSAM samDesired = ( KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE );
	SECURITY_ATTRIBUTES secAttr = { 0, };

	HKEY hKey = nullptr;
	DWORD dwDisposition = 0;
	LSTATUS ret = ::RegCreateKeyExW( HKEY_LOCAL_MACHINE, lpSubKey, Reserved, lpClass, dwOption, samDesired, nullptr, &hKey, &dwDisposition );
	if ( ret == ERROR_SUCCESS ) {
		__noop;
	}

	std::cout << "RegCreateKeyExW: " << ret << std::endl;
	return hKey;
}


int main()
{
	HKEY hKey = _RegCreateKeyExW();

	LPCWSTR lpValueName = L"REG_BINARY_TEST";
	DWORD Reserved = 0;
	DWORD dwType = REG_BINARY;

	DWORD cbSize = sizeof( WCHAR ) * std::wcslen( lpValueName );
	std::vector< BYTE > buffer;
	buffer.resize( cbSize );

	LSTATUS ret = ::RegSetValueExW( hKey, lpValueName, Reserved, dwType, buffer.data(), cbSize );
	if ( ret == ERROR_SUCCESS ) {
		__noop;
	}
	std::cout << "RegSetValueExW: " << ret << ", " << std::endl;
}
