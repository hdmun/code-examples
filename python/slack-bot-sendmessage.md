# 슬랙 봇 메세지 전송

## Http Post, Slack API 방식

https://api.slack.com/methods/chat.postMessage

### 단순 텍스트 메세지 전송하는 코드

```python
import requests

bot_token=''  # 슬랙 앱 페이지 `OAuth & Permissions` 메뉴의 `Bot User OAuth Token` 참조
channel_id= ''  # 채널ID 값, 채널명x

message= '메세지 전송 테스트'
data = {
    'Content-Type': 'application/x-www-form-urlencoded',
    'token': bot_token,
    'channel': channel_id,
    'text': message
}

res = requests.post('https://slack.com/api/chat.postMessage', data=data, verify=False)
print(res.json())
```