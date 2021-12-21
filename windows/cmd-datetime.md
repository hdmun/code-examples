# 배치 스크립트 date time 다루기

> 윈도우 배치 스크립트에서 datetime을 다루어 봅시다.

## batch script

```bat
set YEAR=%date:~2,2%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%

set HH=%time:~0,2%
IF "%HH:~0,1%" == " " SET HH=0%HH:~1,1%
set MM=%time:~3,2%
set SS=%time:~6,2%

set DATE_TIME_MIN=%YEAR%-%MONTH%-%DAY% %HH%:%MM%

echo %date%
echo %time%
echo %DATE_TIME_MIN%
```

## output
```
2021-12-21
11:11:34.81
21-12-21 11:11
```
