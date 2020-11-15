
'''Simple client program'''
import socket
import sys

HOST = 'localhost'
PORT = 55151


import time
import threading
import random

def foo(): # ************************* SET TIMER
    wait_time=25+random.uniform(0,10)
    print(wait_time)
    print(time.ctime())
    threading.Timer(wait_time, foo).start()

foo()

def main(name: str):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:

        #s.connect((HOST, PORT))
        #print('Connected to {}:{}'.format(HOST, PORT))

        s.sendall("Hi, I'm {}".format(name).encode())
        data = s.recv(1024)
        print('Received: {}'.format(data.decode()))
        s.close()
        print('Connection closed')


if __name__ == '__main__':
    main(sys.argv[1])
