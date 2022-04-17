#client v1.0.1
import socket
IP = "127.0.0.1"
PORT = 1618
#connect to server
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (IP, PORT)
sock.connect(server_address)
#receive message
data = sock.recv(1024).decode()
print("content recieved from server is: "+data)
if data == 'Hello':
    sock.send('Hello'.encode())
    data = sock.recv(1024)
    print("conversation successful!")
else:
    print("something went wrong")
    
#close connection
sock.close()