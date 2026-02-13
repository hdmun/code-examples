# Sync Antigravity Skills (Symbolic Link)

`antigravity` 프로젝트의 Skill 폴더를 다른 AI Agent 에서 참조하기 위한 심볼릭 링크 설정 예시

## Command Prompt (CMD)

관리자 권한으로 실행 필요.

```cmd

cd /d "%~dp0"

:: 기존에 잘못 생성된 링크나 폴더 삭제 (주의: 실제 폴더가 아님을 확인하세요)
if exist ".codex\skills" rmdir ".codex\skills"
if exist ".gemini\skills" rmdir ".gemini\skills"
if exist "AGENTS.md" del "AGENTS.md"

:: 폴더 생성
if not exist ".codex" mkdir ".codex"
if not exist ".gemini" mkdir ".gemini"

:: 심볼릭 링크 생성 (절대 경로 방식 사용)
:: mklink /d "%~dp0.codex\rules" "%~dp0.agent\rules"
mklink /d "%~dp0.codex\skills" "%~dp0.agent\skills"
mklink /d "%~dp0.gemini\skills" "%~dp0.agent\skills"
mklink "%~dp0AGENTS.md" "%~dp0GEMINI.md"

pause
```

## .gitignore 설정

심볼릭 링크 폴더가 Git에 커밋되지 않도록 추가.

```text
.codex/skills
.gemini/skills
AGENTS.md
```