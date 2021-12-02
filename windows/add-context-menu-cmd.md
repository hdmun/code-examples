# 탐색기 우클릭 메뉴 추가하기

> 윈도우 탐색기 우클릭 메뉴에 `cmd` 실행 추가하기

## 추가하는 스크립트

```reg
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Folder\shell\runas]
@="관리자: 명령 프롬프트"
"Icon"="cmd.exe"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Folder\shell\runas\command]
@="cmd.exe /s /k pushd \"%V\""


[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Directory\Background\shell\runas]
@="관리자: 명령 프롬프트"
"Icon"="cmd.exe"

[HKEY_LOCAL_MACHINE\SOFTWARE\Classes\Directory\Background\shell\runas\command]
@="cmd.exe /s /k pushd \"%V\""
```


## 제거하는 스크립트

```reg
Windows Registry Editor Version 5.00

[-HKEY_CLASSES_ROOT\Folder\shell\명령 프롬프트]
[-HKEY_CLASSES_ROOT\Folder\shell\명령 프롬프트\command]
[-HKEY_CLASSES_ROOT\Directory\Background\shell\명령 프롬프트]
[-HKEY_CLASSES_ROOT\Directory\Background\shell\명령 프롬프트\command]
```
