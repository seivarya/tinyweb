import requests


try:
    url = "http://127.0.0.1:1025"
    for i in range(5):
        response = requests.get(url)
        print(response)

except Exception as e:
    print(e)
