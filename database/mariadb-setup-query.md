# MariaDB 셋업 쿼리

> MariaDB 설치 후 초기 설정 및 관리에 자주 사용하는 쿼리 모음입니다.

---

## 데이터베이스 생성 (UTF8MB4)

이모지 지원을 위해 `utf8mb4` 문자셋 사용을 권장합니다.

```sql
CREATE DATABASE `database_name` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

---

## 사용자 관리

### 로컬 접속 사용자 추가

```sql
CREATE USER 'new_user'@'localhost' IDENTIFIED BY 'password123!';
GRANT ALL PRIVILEGES ON `database_name`.* TO 'new_user'@'localhost';
FLUSH PRIVILEGES;
```

### 외부 접속 사용자 추가 (특정 IP 혹은 모든 IP)

```sql
-- 모든 IP에서 접속 허용 (%)
CREATE USER 'new_user'@'%' IDENTIFIED BY 'password123!';
GRANT ALL PRIVILEGES ON `database_name`.* TO 'new_user'@'%';

-- 특정 IP에서만 접속 허용
CREATE USER 'new_user'@'192.168.0.100' IDENTIFIED BY 'password123!';

FLUSH PRIVILEGES;
```

### 사용자 삭제

```sql
DROP USER 'new_user'@'localhost';
```

---

## 설정 확인

### 캐릭터셋 확인

```sql
SHOW VARIABLES LIKE 'c%';
```

### 프로세스 리스트 확인 (접속 현황)

```sql
SHOW PROCESSLIST;
```

---

## 윈도우 MariaDB 패스워드 리셋

> mysql 클라이언트 프로그램에 저장해놓고 자꾸 비번을 까먹을 때 사용합니다.

### 1. MariaDB 서비스 중지

윈도우 서비스 관리자(`services.msc`)에서 MariaDB 서비스를 중지합니다.

### 2. 인증 기능 비활성화 모드로 실행

관리자 권한으로 명령 프롬프트(CMD)를 열고 실행합니다. (경로는 버전마다 다를 수 있음)

```cmd
"C:\Program Files\MariaDB 10.5\bin\mysqld.exe" --skip-grant-tables
```

### 3. 새로운 커맨드 창에서 패스워드 변경

```sql
-- mysql 접속 후 실행
USE mysql;
FLUSH PRIVILEGES;

-- MariaDB 10.4 이상 버전
ALTER USER 'root'@'localhost' IDENTIFIED BY 'new_password';

-- 이전 버전 혹은 위 쿼리가 안될 때
-- SET PASSWORD FOR 'root'@'localhost' = PASSWORD('new_password');

FLUSH PRIVILEGES;
```
