
from sys import pycache_prefix

# logging 사용하기


```python
import logging


def get_logger(log_filename: str):
    logger = logging.getLogger('logger')
    if len(logger.handlers) > 0:
        return logger  # Logger already set handler

    formatter = logging.Formatter(
        '[%(levelname)s|%(name)s|%(filename)s:%(lineno)s] %(asctime)s > %(message)s')
    stream_handler = logging.StreamHandler()
    stream_handler.setFormatter(formatter)
    logger.addHandler(stream_handler)

    file_handler = logging.FileHandler(log_filename, mode='w')
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)
    logger.setLevel(logging.DEBUG)

    return logger


logger = get_logger()
logger.info('test message')
```