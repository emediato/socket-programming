# imports
import socket
import sys
import re
from struct import pack, unpack
import datetime as dt

# Definitions
CONNECTIONS_ALLOWED = 5
BUFFER_SIZE = 414 # Maximum size of a message (w/ header)
TIMEOUT = 4

# Message types
KEYREQ = 5
TOPOREQ = 6
KEYFLOOD = 7
TOPOFLOOD = 8
RESP = 9

# Info received from prompt
serv_info = sys.argv[1]
(host, port) = serv_info.split(':')
address = (host, int(port))

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.settimeout(TIMEOUT)
nseq = 0

# Returns a REQ message
def generateREQ(type_req, nseq, text):

	if type_req == KEYREQ:
		req_msg = pack('!Hi', KEYREQ, nseq) + text.encode()
	elif type_req == TOPOREQ:
		req_msg = pack('!Hi', TOPOREQ, nseq)
	return req_msg

print("-> To search for a key, type ? <key>")
print("-> To see the network topology, type T")
print("-> To exit, type Q")

while True:

	print('\n')
	command = input()
	command = command.split(' ')

	# Send REQ message
	if command[0] == '?' or command[0] == 'T':

		# Search a key
		if command[0] == '?':
			# print('?')
			key = command[1]
			req_msg = generateREQ(KEYREQ, nseq, key)
		# See the network topology
		elif command[0] == 'T':
			# print('T')
			req_msg = generateREQ(TOPOREQ, nseq, "")
		sock.sendto(req_msg, address)

		i = 0
		received = False
		while True:
			try:
				msg, source = sock.recvfrom(BUFFER_SIZE)
				(type_recv, nseq_recv) = unpack('!Hi', msg[0:6])
				key = msg[6:].decode()

				# Wrong message type or different sequence number 
				if type_recv != RESP or nseq_recv != nseq:
					print("Wrong message received from %s:%s" % (source[0], source[1]))
				else:
					print("%s %s:%s" %(key, source[0], source[1]))
				received = True

			except socket.timeout:
				if received == True:
					break
				elif i == 0:
					# Increase sequence number to send the message again
					nseq += 1
					if command[0] == '?':
						req_msg = generateREQ(KEYREQ, nseq, key)
					elif command[0] == 'T':
						req_msg = generateREQ(TOPOREQ, nseq, "")
					sock.sendto(req_msg, address)
				elif i == 1:
					print("No response received")
					break
			i += 1

		# Increase sequence number to next command
		nseq += 1
	elif command[0] == 'Q':
		# print('Q')
		break
	else:
		print("Error! Wrong input.")

# Closing client socket
sock.close()
