
# 파일 속성 변경

```
pip install pypiwin32
```

## 날짜 속성 변경

```python
import ntsecuritycon
import pywintypes
import win32con
import win32file


def change_file_time(filename: str, timestamp: float):
    winfile = win32file.CreateFile(
        filename,
        ntsecuritycon.FILE_WRITE_ATTRIBUTES,
        0,
        None,
        win32con.OPEN_EXISTING,
        0,
        None)

    wintime = pywintypes.Time(timestamp)
    create_time = wintime
    last_access_time = None
    modified_time = wintime
    win32file.SetFileTime(winfile, create_time, last_access_time, modified_time)
    winfile.close()

if __name__ == '__main__':
    filepath = r''
    change_file_time(filename=filepath, timestamp=datetime.utcnow().timestamp())
```


### mp4 미디어 작성 날짜 가져오기

```python
import pywintypes

from datetime import datetime
from win32com.propsys import propsys, pscon
from win32comext.shell import shellcon


def get_media_date_encoded(path: str, onlystr: bool=False):
    try:
        properties = propsys.SHGetPropertyStoreFromParsingName(
            path, None, shellcon.GPS_READWRITE, propsys.IID_IPropertyStore)
    except pywintypes.com_error:
        return None

    # type of <class 'pywintypes.datetime'>
    prop_dt = properties.GetValue(pscon.PKEY_Media_DateEncoded).GetValue()
    properties = None  # release
    if onlystr:
        format_dt = '%Y-%m-%d %H:%M:S'
        return datetime.strptime(prop_dt.strftime(format_dt), format_dt)
    return prop_dt


if __name__ == '__main__':
    filepath = r''
    media_created = get_media_date_encoded(path=filepath)
    print(media_created, type(media_created))
```


### mp4 미디어 작성 날짜 변경하기

```python
import pythoncom
import pywintypes

from datetime import datetime
from win32com.propsys import propsys, pscon
from win32comext.shell import shellcon


def set_media_date_encoded(path: str, timestamp: float):
    properties = propsys.SHGetPropertyStoreFromParsingName(path, None, shellcon.GPS_READWRITE, propsys.IID_IPropertyStore)
    prop_var_date = propsys.PROPVARIANTType(pywintypes.Time(timestamp), pythoncom.VT_DATE)
    properties.SetValue(pscon.PKEY_Media_DateEncoded, prop_var_date)
    properties.Commit()
    properties = None


if __name__ == '__main__':
    filepath = r''
    set_media_date_encoded(path=filepath, timestamp=datetime.utcnow().timestamp())
```
