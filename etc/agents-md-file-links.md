# Sync Antigravity Skills (Symbolic Link)

`antigravity` 프로젝트의 Skill 폴더를 현재 프로젝트에서 참조하기 위한 심볼릭 링크 설정 예시입니다.

## Command Prompt (CMD)

관리자 권한으로 실행 필요.

```cmd
:: Syntax: mklink /D "Target_Path" "Source_Path"

cd /d "%~dp0"


:: 예시: 현재 폴더에 .codex\rules 라는 이름으로 링크 생성
mklink /D ".codex\rules" ".agent/rules"

mklink "GEMINI.md" "AGENTS.md"

pause
```

## .gitignore 설정

심볼릭 링크 폴더가 Git에 커밋되지 않도록 추가.

```text
.skills/
```