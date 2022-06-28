# git 리비전 c++ 매크로 만들기

> git 저장소 리비전을 c++ 매크로로 만드는 방법

## 템플릿 파일

```cpp
// git_revision.h.template
#ifndef _GIT_REVISION_H_
#define _GIT_REVISION_H_

#define GIT_REVISION "$COMMIT_HASH$"
#endif
```

## 생성 배치 파일

```bat

rem get git commit hash
set COMMIT_HASH_TEMP=git_commit_hash.tmp

if exist %COMMIT_HASH_TEMP% del %COMMIT_HASH_TEMP%

git rev-parse --verify HEAD > %COMMIT_HASH_TEMP%

set /p GITHASH_TMP= < %COMMIT_HASH_TEMP%


set HEADER_TEMPLATE=git_revision.h.template
set HEADER_FILE_TMP=git_revision.h.tmp
set HEADER_FILE=git_revision.h
::if exist %HEADER_FILE% del %HEADER_FILE%

powershell.exe "(Get-Content %HEADER_TEMPLATE%) -replace '\$COMMIT_HASH\$', '%GITHASH_TMP%' | Out-File -encoding ASCII %HEADER_FILE_TMP%"
fc %HEADER_FILE_TMP% %HEADER_FILE%
if %errorlevel% equ 0 exit /b 0

echo F | xcopy %HEADER_FILE_TMP% %HEADER_FILE% /y /d

if exist %COMMIT_HASH_TEMP% del %COMMIT_HASH_TEMP%

exit /b 0

:ERROR

if exist %COMMIT_HASH_TEMP% del %COMMIT_HASH_TEMP%

exit /b 1
```
