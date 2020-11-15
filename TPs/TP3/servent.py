# imports
import socket
import sys
import re
from struct import pack, unpack
import datetime as dt

# Definitions
CONNECTIONS_ALLOWED = 5
BUFFER_SIZE = 414 # Maximum size of a message (w/ header)

# Message types
KEYREQ = 5
TOPOREQ = 6
KEYFLOOD = 7
TOPOFLOOD = 8
RESP = 9


# Returns KEYFLOOD or TOPOFLOOD message
def generateFLOOD(reqtype, client, nseq, info):
	ip, port = client

	# Distinguish between KEYFLOOD and TOPOFLOOD
	if reqtype == KEYREQ:
		msgtype = KEYFLOOD
	elif reqtype == TOPOREQ:
		msgtype = TOPOFLOOD

	# Mount message in bytes to be sent
	msg = pack('!HHi', msgtype, 3, nseq) + socket.inet_aton(ip) + pack('!H', port) + info.encode() 

	return msg


# Returns a RESP message
def generateRESP(nseq, text):
	msg = pack('!Hi', RESP, nseq) + text.encode()
	return msg


# Update KEYFLOOD/TOPOFLOOD message
def updateFLOOD(floodtype, ttl, nseq, src_ip, src_port, info):
	msg = pack('!HHiiH', floodtype, ttl, nseq, src_ip, src_port) + info.encode()
	return msg


# Info received from prompt
serv_port = int(sys.argv[1])
key_file = sys.argv[2]
connections_list = sys.argv[3:]


# Initializing UDP socket
print("[%s] Initializing UDP socket" % dt.datetime.now())
address = ('', serv_port)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(address)


# Reading keys and values from source file
keys_values = {}

with open(key_file, 'r') as infile:
	for line in infile:
		if line[0] not in ['#', '\n']:
			[key, value] = re.split('\t| ', line, 1) # split only by first space/tab
			value.replace('\n', '') # Remove newline characters
			keys_values[key] = value
print("[%s] Read keys + values from file" % dt.datetime.now())


# Create list of connections
connections = []

for endpoint in connections_list:
	(host, port) = endpoint.split(':')
	connections.append((host, int(port)))



# Receive messages
recvd_msgs = [] # List of messages already received

print("[%s] Ready to receive messages" % dt.datetime.now())
while True:
	msg, source = sock.recvfrom(BUFFER_SIZE)
	(msg_type,) = unpack('!H', msg[0:2]) # First two bytes tell message type


	# Handle KEYREQ messages
	if msg_type == KEYREQ:
		print("[%s] KEYREQ received from %s" % (dt.datetime.now(), source))
		(msg_type, nseq) = unpack('!Hi', msg[0:6])
		key = msg[6:].decode()

		# Send KEYFLOOD to all servent connections
		flood_msg = generateFLOOD(KEYREQ, source, nseq, key)
		for host in connections:
			sock.sendto(flood_msg, host)
			print("[%s] KEYFLOOD sent to %s" % (dt.datetime.now(), host))

		# Search key in dictionary. If found, send to client
		if key in keys_values:
			resp_msg = generateRESP(nseq, keys_values[key])
			sock.sendto(resp_msg, source)
			print("[%s] RESP sent to %s" % (dt.datetime.now(), source))


	# Handle TOPOREQ messages
	elif msg_type == TOPOREQ:
		print("[%s] TOPOREQ received from %s" % (dt.datetime.now(), source))
		(msg_type, nseq) = unpack('!Hi', msg[0:6])

		# Generate and send KEYFLOOD to all servent connections
		myaddress = socket.gethostbyname(socket.gethostname()) + ':' + str(serv_port)
		flood_msg = generateFLOOD(TOPOREQ, source, nseq, myaddress)

		for host in connections:
			sock.sendto(flood_msg, host)
			print("[%s] TOPOFLOOD sent to %s" % (dt.datetime.now(), host))

		# Generate and send RESP to client
		resp_msg = generateRESP(nseq, myaddress)
		sock.sendto(resp_msg, source)
		print("[%s] RESP sent to %s" % (dt.datetime.now(), source))


	# Handle KEYFLOOD messages
	elif msg_type == KEYFLOOD:
		(msg_type, ttl, nseq, src_ip, src_port) = unpack('!HHiiH', msg[0:14])
		info = msg[14:].decode()

		# Only handle new flood messages
		if (src_ip, src_port, nseq) not in recvd_msgs:
			print("[%s] KEYFLOOD received from %s" % (dt.datetime.now(), source))
			recvd_msgs.append((src_ip, src_port, nseq))
			ttl -= 1 # Decrements TTL

			# Send KEYFLOOD to all servent connections only if TTL > 0
			if ttl > 0:
				flood_msg = updateFLOOD(KEYFLOOD, ttl, nseq, src_ip, src_port, info)
				for host in connections:
					# Send to all connections except the one who sent the message to the current servent
					if host != source: 
						sock.sendto(flood_msg, host)
						print("[%s] KEYFLOOD forwarded to %s" % (dt.datetime.now(), host))

			# Search key in dictionary. If found, send to client
			if info in keys_values:
				resp_msg = generateRESP(nseq, keys_values[info])
				client = (socket.inet_ntoa(pack('!i', src_ip)), src_port)
				sock.sendto(resp_msg, client)
				print("[%s] RESP sent to %s" % (dt.datetime.now(), client))


	# Handle TOPOFLOOD messages
	elif msg_type == TOPOFLOOD:
		(msg_type, ttl, nseq, src_ip, src_port) = unpack('!HHiiH', msg[0:14])
		info = msg[14:].decode()

		# Only handle new flood messages
		if (src_ip, src_port, nseq) not in recvd_msgs: 
			print("[%s] TOPOFLOOD received from %s" % (dt.datetime.now(), source))
			recvd_msgs.append((src_ip, src_port, nseq))
			ttl -= 1 # Decrements TTL

			myaddress = socket.gethostbyname(socket.gethostname()) + ':' + str(serv_port)
			info += ' ' + myaddress

			# Send KEYFLOOD to all servent connections only if TTL > 0
			if ttl > 0:
				flood_msg = updateFLOOD(TOPOFLOOD, ttl, nseq, src_ip, src_port, info)
				for host in connections:
					# Send to all connections except the one who sent the message to the current servent
					if host != source: 
						sock.sendto(flood_msg, host)
						print("[%s] TOPOFLOOD forwarded to %s" % (dt.datetime.now(), host))

			# Generate and send RESP to client
			resp_msg = generateRESP(nseq, info)
			client = (socket.inet_ntoa(pack('!i', src_ip)), src_port)
			sock.sendto(resp_msg, client)
			print("[%s] RESP sent to %s" % (dt.datetime.now(), client))


	else:
		print("[%s] Unknown message type received: %d from %s" % (dt.datetime.now(), msg_type, source))

# Closing servent socket
sock.close()