
#socket_echo_server_dgram.py
# https://github.com/abdulqadirs/distance-vector-routing-protocol/blob/master/update.py
# https://github.com/prabhuvashwin/Computer-Networks/blob/master/Distance%20Vector%20Routing/RouterAdmin.py
#   https://github.com/Ahmad-Magdy-Osman/ComputerNetworks/tree/master/8-Distance%20Vector%20Routing%20Protocol


import socket
import sys

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = ('localhost', 55151)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)

while True:
    print('\nwaiting to receive message')
    data, address = sock.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)

    if data:
        sent = sock.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))