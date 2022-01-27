# 로컬 보안 정책 cli로 수정하기

`secedit` 툴로 로컬 보안 정책을 변경할 수 있다.

설정 파일을 괸라하여 자동화할 수 있는 여지가 있다.

```
secedit [/configure | /analyze | /import | /export | /validate | /
generaterollback]
```

각 옵션 값 까지 입력 후 실행하면 도움말이 출력된다.


## 사용자 보안 설정 출력

```
secedit /export /areas USER_RIGHTS /cfg c:\se_user_rights.inf
```


## 사용자 보안 설정 반영

```
secedit /import /areas USER_RIGHTS /cfg c:\se_user_rights.inf
```
