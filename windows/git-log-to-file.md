# git 명령어들

## git 커밋 로그 출력하기

```cmd
git log --pretty=format:"%h | %ad | %s" --after="2023-01-01" --until="2023-01-31" --author="hdmun" --date=iso > ..\2023_01_hdmun.log
```


## TortoiseGit Pull 커맨드

```cmd
start /D "C:\Program Files\TortoiseGit\bin" TortoiseGitProc.exe /command:pull /path:"repo path"
```