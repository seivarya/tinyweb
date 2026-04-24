import requests
import sys

PORT = 1028
URL = f"http://127.0.0.1:{PORT}"


def execute_request(method, url, **kwargs):
    print(f"==+ {method.upper()} +==")
    try:
        r = requests.request(method, url, timeout=5, **kwargs)
        print(f"==+ Status: {r.status_code} +==")
        print(f"==+ Headers: {dict(r.headers)} +==")
        print(f"==+ Body: {r.text} +==")
    except requests.ConnectionError:
        print(f"==+ Error: Connection refused by {url} +==")
    except requests.Timeout:
        print(f"==+ Error: Request to {url} timed out +==")
    except Exception as e:
        print(f"==+ Error: {str(e)} +==")


def main():
    while True:
        try:
            status = int(
                input(
                    "Enter 1 for get()\n"
                    "      2 for post()\n"
                    "      3 for put()\n"
                    "      4 for delete()\n"
                    "      5 for patch()\n"
                    "      6 for head()\n"
                    "      7 for options()\n"
                    "      8 to quit\n"
                    "> "
                )
            )

            match status:
                case 1:
                    execute_request("get", URL)
                case 2:
                    execute_request("post", URL, json={"msg": "hello from POST"})
                case 3:
                    execute_request("put", URL, json={"msg": "hello from PUT"})
                case 4:
                    execute_request("delete", URL)
                case 5:
                    execute_request("patch", URL, json={"msg": "hello from PATCH"})
                case 6:
                    execute_request("head", URL)
                case 7:
                    execute_request("options", URL)
                case 8:
                    print("Exiting.")
                    sys.exit(0)
                case _:
                    print("Invalid input.")

        except ValueError:
            print("Please enter a valid integer.")
        except KeyboardInterrupt:
            print("\nExiting.")
            sys.exit(0)


if __name__ == "__main__":
    main()