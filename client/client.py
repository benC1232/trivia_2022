#client v1.0.1
import socket
IP = "127.0.0.1"
PORT = "1618"
#connect to server
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((IP, PORT))
#receive message
data = socket.recv(1024).decode()
print("content recieved from the server: " + data)
if data == 'Hello':
    socket.send('Hello'.encode())
    data = socket.recv(1024)
    print("conversation successful!")
else:
    print("something went wrong")
    
#close connection
socket.close()