#client v1.0.2
import socket

server_address = ('127.0.0.1', 1618)
choice = 0

while choice != 3:
    choice = int(input("1.login\n2.register\n3.exit\n"))
    if choice == 1:
        json = '{"type":"login","username":"' + input("username:") + '","password":"' + input("password:") + '"}'
        
    elif choice == 2:
        json = '{"type":"register","username":"' + input("username:") + '","password":"' + input("password:") + '","mail":"' + input("mail:") + '"}'
    else:
        print("invalid choice")
    