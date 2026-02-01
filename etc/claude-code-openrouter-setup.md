# Claude Code + OpenRouter 설정 가이드 (Claude Code Router 활용)

이 문서는 OpenRouter를 통해 Claude Code를 경제적이고 유연하게 사용하는 방법을 설명합니다. 특히 공식 가이드 방식과 더불어, 로컬 프록시 도구(`ccr-next`)를 사용하는 심화 설정법을 다룹니다.

참고 링크:
- [공식 가이드 (OpenRouter)](https://openrouter.ai/docs/guides/guides/claude-code-integration)
- [ccr-next GitHub (Claude Code Router)](https://github.com/Darthwares/ccr-next)
- [관련 블로그 가이드 (Velog)](https://velog.io/@composite/%ED%9D%99%EC%88%98%EC%A0%80%EB%A5%BC-%EC%9C%84%ED%95%9C-Claude-Code-Claude-Code-Router)

---

## 1. 사전 준비 사항

- **Node.js**: v18 이상 권장
- **Claude Code CLI**: `npm install -g @anthropic-ai/claude-code`
- **OpenRouter API Key**: [openrouter.ai](https://openrouter.ai/)에서 발급

---

## 2. 설정 방법 (두 가지 방식)

### 방식 A: 단순 환경 변수 설정 (공식 권장)
별도의 도구 없이 환경 변수만으로 연결하는 가장 간단한 방법입니다.

**PowerShell (Windows):**
```powershell
$env:ANTHROPIC_BASE_URL = "https://openrouter.ai/api"
$env:ANTHROPIC_API_KEY = ""
$env:ANTHROPIC_AUTH_TOKEN = "your-openrouter-api-key"
```

**Bash/Zsh:**
```bash
export ANTHROPIC_BASE_URL="https://openrouter.ai/api"
export ANTHROPIC_API_KEY=""
export ANTHROPIC_AUTH_TOKEN="your-openrouter-api-key"
```

### 방식 B: Claude Code Router (`ccr-next`) 사용 (권장)
로컬 프록시를 통해 여러 모델을 교체하거나 OpenRouter 외의 다른 제공자도 통합할 수 있는 유연한 방식입니다.

1. **도구 설치:**
   ```bash
   npm install -g ccr-next
   ```

2. **OpenRouter 제공자 등록:**
   ```bash
   ccr provider add openrouter https://openrouter.ai/api/v1/chat/completions YOUR_OPENROUTER_API_KEY "anthropic/claude-3.5-sonnet,google/gemini-2.0-flash-001"
   ```

3. **기본 라우터 설정:**
   `~/.claude-code-router/config.json` 파일을 열어 기본 모델을 설정합니다.
   ```json
   {
     "Router": {
       "default": "openrouter,anthropic/claude-3.5-sonnet"
     }
   }
   ```

4. **Claude Code 실행:**
   환경 변수를 자동으로 잡아주는 활성화 명령어를 사용하거나, `ccr code` 명령어로 실행합니다.
   ```bash
   # 방법 1: 직접 실행
   ccr code

   # 방법 2: 셸 활성화 후 claude 직접 사용 (Bash/Zsh)
   eval "$(ccr activate)"
   claude
   ```

---

## 3. 주요 팁 및 주의 사항

- **모델 식별자**: OpenRouter 사용 시 모델명 앞에 제공자 이름을 붙여야 합니다 (예: `anthropic/claude-3.5-sonnet`).
- **비용 최적화**: OpenRouter의 **Free Models**를 연결하여 테스트 용도로 무료 사용이 가능합니다.
- **예산 제한**: OpenRouter 설정 페이지에서 API Key마다 예산 제한(Limit)을 걸어 예상치 못한 과금을 방지하세요.
- **오류 발생 시**: `ccr restart` 명령어로 로컬 프록시 서버를 재시작해 보세요.

---

## 4. 요약 (Quick Start)
1. OpenRouter 키 발급
2. `ccr-next` 설치
3. `ccr provider add`로 키 등록
4. `ccr code` 실행