import requests

url = "http://127.0.0.1:44681"

try:
    r = requests.get(url)
    print(f"status code:: ", r.status_code)
    print(f"encoding :: ", r.encoding)
    print(f"content :: ", r.text)
except Exception as e:
    print(e)





