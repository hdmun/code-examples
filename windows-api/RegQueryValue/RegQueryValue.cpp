#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
#include <vector>


HKEY _RegCreateKeyExW()
{
	LPCWSTR lpSubKey = L"SOFTWARE\RegTest";
	DWORD Reserved = 0;
	LPWSTR lpClass = nullptr;
	DWORD dwOption = REG_OPTION_NON_VOLATILE;
	REGSAM samDesired = ( KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE );
	SECURITY_ATTRIBUTES secAttr = { 0, };

	HKEY hKey = nullptr;
	DWORD dwDisposition = 0;
	LSTATUS ret = ::RegCreateKeyExW( HKEY_LOCAL_MACHINE, lpSubKey, Reserved, lpClass, dwOption, samDesired, nullptr, &hKey, &dwDisposition );

	std::cout << "RegCreateKeyExW: " << ret << std::endl;
	return hKey;
}


int main()
{
	HKEY hKey = _RegCreateKeyExW();

	LPCWSTR lpValueName = L"REG_BINARY_TEST";
	DWORD dwReserved = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwLen = 0;
	LSTATUS ret = ::RegQueryValueExW( hKey, lpValueName, &dwReserved, &dwType, nullptr, &dwLen );
	if ( ret != ERROR_SUCCESS || dwType != REG_BINARY || dwLen == 0 ) {
		return;
	}

	std::vector<BYTE> aData;
	aData.resize( dwLen );
	ret = ::RegQueryValueExW( hKey, lpValueName, &dwReserved, &dwType, aData.data(), &dwLen );
	if ( ret != ERROR_SUCCESS ) {
		aData.clear();
	}
}
