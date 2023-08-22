from flask import Flask, request, jsonify
import socket
import threading

app = Flask(__name__)

# Create a dictionary to store responses for each request
responses = {}
responses_lock = threading.Lock()

def handle_request(name):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect(('127.0.0.1', 12345))
        client_socket.send(name.encode())

        response = client_socket.recv(1024).decode()

    # Store/Updating the response in the dictionary
    with responses_lock:
        responses[name] = response
    # Printing here each responce forming a thread
        print("response from C code is", response)

@app.route('/check_name', methods=['GET'])
def check_name():
    name = request.args.get('name')

    # Check if the response is already available 
    with responses_lock:
        if name in responses:
            response = responses[name]
        else:
            # Create a new thread to handle the request
            thread = threading.Thread(target=lambda: handle_request(name))
            thread.start()
            response = "Request processing started"

    # Form the JSON response based on the response from the C program
    if "not" in response:
        message = "name is registered thank you"
    else:
        message = "name is not registered thank you"

    return jsonify(message)

if __name__ == '__main__':
    app.run(debug=True)

