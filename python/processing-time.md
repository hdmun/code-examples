# 코드 실행시간 단순 계산


```python
import datetime
import time


start = time.time()
time.sleep(10)
end = time.time()

sec = (end - start)
result = datetime.timedelta(seconds=sec)
print(result, start, end)
```