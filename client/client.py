#client v1.0.2

"""
this file is the client side of the trivia game (v1.0.2)
it is a simple client that connects to the server and sends the user's choice to the server
the server will then send back the answer to the user
"""
from typing import List, Set, Dict, Tuple, Optional
import socket
import json
import ast



server_address: tuple= ('127.0.0.1', 9999)


def sizeOfJson(size: int)->str:
    #returns a string four chars long with the size of the json, if the size is less than 4 chars long it will be padded with 0's
    return size.to_bytes(4, byteorder='big').decode()

def menu() -> tuple:
    choice:int = 0
    output: str = ''
    while choice > 3 or choice < 1:
        choice = int(input("1.login\n2.register\n3.exit\n"))
        if choice == 1:
            output = {"type":"login","username":input("username:"),"password":input("password:")}
        elif choice == 2:
            output = {"type":"register","username":input("username:"),"password":input("password:"),"mail":input("mail:")}
        else:
            print("invalid choice")

    return (json.dumps(output), choice)


def build_request(data: Tuple[str, str]) -> str:
    """
    message builder:
    returns a string in the following format
    |msg code|size of json|json
    """
    json_data, msg_code = data
    return str(msg_code) + sizeOfJson(len(json_data)) + json_data

def unpack_response(data: str) -> Tuple[dict, int]:
    """
    message unpacker:
    returns a tuple of the json and the msg code
    """
    msg_code = int(data[0])
    json_data = json.loads(data[5:])
    return json_data, msg_code

    
def server_commuinication() -> None:
    """
    client side communication with server
    """
    while 1:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(server_address)
            data, choice = menu()
            if choice == 3:
                break
            s.sendall(build_request((data,choice)).encode())
            data = s.recv(1024)
            print(data.decode())



if __name__ == '__main__':
    server_commuinication()


