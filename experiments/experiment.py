import requests

url = input("enter url: ")

# some sample data for POST/PUT/PATCH
payload = {"meh": "listen to get lucky"}

try:
    # GET
    r = requests.get(url)
    print("=== GET ===")
    print("Status:", r.status_code)
    print("Body:\n", r.text, "\n")

    # POST
    r = requests.post(url, json=payload)
    print("=== POST ===")
    print("Status:", r.status_code)
    print("Body:\n", r.text, "\n")

    # PUT
    r = requests.put(url, json=payload)
    print("=== PUT ===")
    print("Status:", r.status_code)
    print("Body:\n", r.text, "\n")

    # PATCH
    r = requests.patch(url, json={"patched": True})
    print("=== PATCH ===")
    print("Status:", r.status_code)
    print("Body:\n", r.text, "\n")

    # DELETE
    r = requests.delete(url)
    print("=== DELETE ===")
    print("Status:", r.status_code)
    print("Body:\n", r.text, "\n")

except Exception as e:
    print("Error:", e)

