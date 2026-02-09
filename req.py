import requests

PORT = 1028
URL = f"http://127.0.0.1:{PORT}"

def main():
    while True:
        try:
            status = int(input(
                "Enter 1 for get()\n"
                    "2 for post()\n"
                    "3 for put()\n"
                    "4 for delete()\n"
                    "5 for patch()\n"
                    "6 for head()\n"
                    "7 for options()\n"
                    "8 to quit\n"
                    "> "
            ))

            match status:
                case 1:
                    get()
                case 2:
                    post()
                case 3:
                    put()
                case 4:
                    delete()
                case 5:
                    patch()
                case 6:
                    head()
                case 7:
                    options()
                case 8:
                    print("Exiting.")
                    break
                case _:
                    print("Invalid input.")

        except ValueError:
            print("Please enter a valid integer.")

def get():
    print("==+ GET +==")
    r = requests.get(URL)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")

def post():
    print("==+ POST +==")
    payload = {"msg": "hello from POST"}
    r = requests.post(URL, json=payload)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")

def put():
    print("==+ PUT +==")
    payload = {"msg": "hello from PUT"}
    r = requests.put(URL, json=payload)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")

def delete():
    print("==+ DELETE +==")
    r = requests.delete(URL)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")

def patch():
    print("==+ PATCH +==")
    payload = {"msg": "hello from PATCH"}
    r = requests.patch(URL, json=payload)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")

def head():
    print("==+ HEAD +==")
    r = requests.head(URL)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")  # r.text usually empty for HEAD

def options():
    print("==+ OPTIONS +==")
    r = requests.options(URL)
    print(f"==+ Status: {r.status_code} +==")
    print(f"==+ Headers: {r.headers} +==")
    print(f"==+ Body: {r.text} +==")


if __name__ == "__main__":
    main()
