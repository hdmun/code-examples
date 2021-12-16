# 슬랙 봇 메세지 전송 with Powershell

## Http Post, Slack API 방식

https://api.slack.com/methods/chat.postMessage

### 단순 텍스트 메세지 전송하는 코드

```powershell
$Url = "https://slack.com/api/chat.postMessage"
$headers = @{
    'Content-Type' = 'application/x-www-form-urlencoded'
}
$Body = @{
    token = ""
    channel = ""
    text = "`powershell`에서 보내는 메세지 테스트"
}
Invoke-RestMethod -Method 'Post' -Uri $url -Body $body
```
