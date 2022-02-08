# Windows 11 탐색기 우클릭 메뉴 Windows 10으로 변경하기

## 변경 스크립트

`InprocServer32` 값 추가

```reg
Windows Registry Editor Version 5.00

[HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\InprocServer32]
@=""
```

`explorer.exe` 프로세스 종료 후 재실행하면 적용


## 원복 스크립트

레지스트리 추가 했던걸 삭제

```reg
Windows Registry Editor Version 5.00

[-HKEY_CURRENT_USER\Software\Classes\CLSID\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}]
```

