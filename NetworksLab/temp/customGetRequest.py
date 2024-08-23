import http.client
import time

host = 'localhost'
port = 1596

while True:
    try:
        print(f"Attempting to connect to {host}:{port}")
        conn = http.client.HTTPConnection(host, port)
        conn.request("GET", "/")
        response = conn.getresponse()
        print(f"Status Code: {response.status}")
        print(f"Response: {response.read().decode('utf-8')[:100]}")  # Print first 100 characters of the response
        conn.close()
        
    except ConnectionRefusedError:
        print(f"Connection refused by {host}:{port}")
        
    except Exception as e:
        print(f"An error occurred: {e}")

    # time.sleep(1)  # Sleep for 1 second
