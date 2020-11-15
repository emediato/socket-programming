# imports
import socket
import select
import sys
import os
from struct import pack, unpack

# Message types
OK = 1
ERRO = 2
OI = 3
FLW = 4
MSG = 5
CREQ = 6
CLIST = 7

# Definition of server's identifier
SERVER_ID = 65535


# Create an OK message to be sent
def generateOK(dst, seq):
	msg = pack('!HHHH', OK, SERVER_ID, dst, seq)
	return msg


# Create an ERRO message to be sent
def generateERRO(dst, seq):
	msg = pack('!HHHH', ERRO, SERVER_ID, dst, seq)
	return msg

# Create a CLIST message to be sent
def generateCLIST(clients_dict, dst, seq):
	num_clients = len(clients_dict)
	id_list = list(clients_dict.values())
	msg = pack('!5H', CLIST, SERVER_ID, dst, seq, num_clients)

	for cli_id in id_list:
		msg = msg + pack('!H', cli_id)

	return msg


# Definitions required to initialize socket
HOST, PORT = '0.0.0.0', int(sys.argv[1])
HEADER_SIZE = 8
CONNECTIONS_ALLOWED = 255
TIMEOUT = 5 	# 5 seconds

# Count of clients accepted
n_clients = 0

# Create an INET, STREAMING socket.
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to a public host and well-know port.
try:
	server_socket.bind((HOST, PORT))
except:
	print("bind: address already in use")
	os._exit(1)

# Enables the server to accept connections.
server_socket.listen(CONNECTIONS_ALLOWED)

# List of server + client sockets with identifiers
socket_list = [server_socket]

# Dict of valid clients with identifiers
clients = {}

while True:
	try:
		readable, writable, exceptional = select.select(socket_list, socket_list, socket_list)
		
		# Handle all readable sockets
		for s in readable:

			# Case 1: s is the server socket -> accept new connection 
			if s is server_socket:
				(client_socket, client_address) = s.accept()
				s.settimeout(TIMEOUT)
				client_socket.settimeout(TIMEOUT)
				socket_list.append(client_socket)

			# Case 2: established connection with client that sent data
			else:
				try:
					# Receives message header
					data = s.recv(HEADER_SIZE)

					# Do something only if socket received something
					if data != b'':

						# Discover and handle what type of message it is (unpack, ...)
						header = unpack('!HHHH', data) # 4 unsigned short = 8 bytes
						msg_type = header[0]
						src_id = header[1]
						dst_id = header[2]
						seq_num = header[3]

						# If msg is OI, check list of clients and add new connection
						if msg_type == OI:
							
							# Check if src_id = 0
							if src_id == 0:
								n_clients += 1 # id will increase as we connect new clients
								n_clients %= 65535 # reset ID when it comes to 65534+

								clients[s] = n_clients
								print("OI: novo cliente conectado: id %d" % n_clients)
								
								# Send OK message to client
								client_id = clients[s]
								msg = generateOK(client_id, seq_num)
								s.send(msg)

						# If msg is FLW, remove client from list and send OK
						elif msg_type == FLW:
							if src_id == clients[s]:
								del clients[s]
								msg = generateOK(src_id, seq_num)
								s.send(msg)
								print("FLW: cliente %d desconectado" % src_id)
							else:
								generateERRO(src_id, seq_num)
								print("FLW: ID origem incorreto")


						# If msg is MSG, deliver msg to destination
						elif msg_type == MSG:

							# Receives size and text from message
							data = s.recv(2)
							msg_size = unpack('!H', data)[0]
							data = s.recv(msg_size)
							msg_text = data.decode()

							# Check if source ID is correct
							if src_id == clients[s]:

								# Check if it's a broadcast message
								if dst_id == 0:

									# Send OK to source
									ok_msg = generateOK(src_id, seq_num)
									s.send(ok_msg)
									print("MSG: mensagem de %d para broadcast" % src_id)

									# Forward message to all clients connected
									msg = pack('!HHHHH', msg_type, src_id, dst_id, seq_num, msg_size)
									for client in list(clients.keys()):
										# Don't send message to source
										if clients[client] != src_id: 
											client.send(msg)
											client.send(msg_text.encode())
										
											# Wait for OK
											try:
												data = client.recv(HEADER_SIZE)
												header = unpack('!HHHH', data) # 4 unsigned short = 8 bytes
												if header[0] == OK:
													print("MSG: entregue para %d com sucesso" % clients[client])

											except socket.timeout:
												del clients[client]
												socket_list.remove(client)
												client.close()
												print("MSG: cliente %d inativo. Conexão encerrada" % clients[client])



								# Unicast. Check if destination exists
								else:
									if dst_id in clients.values():

										# Forward message to destination
										for sock, cli_id in clients.items():
											if dst_id == cli_id:
												dst_sock = sock 

										msg = pack('!HHHHH', msg_type, src_id, dst_id, seq_num, msg_size)
										dst_sock.send(msg)
										dst_sock.send(msg_text.encode())

										# Wait for OK
										try:
											data = dst_sock.recv(HEADER_SIZE)
											header = unpack('!HHHH', data) # 4 unsigned short = 8 bytes
											if header[0] == OK:
												print("MSG: mensagem enviada de %d para %d" % (src_id, dst_id))

											# Send OK to source
											ok_msg = generateOK(src_id, seq_num)
											s.send(ok_msg)

										except socket.timeout:
											del clients[dst_sock]
											dst_sock.close()
											socket_list.remove(dst_sock)
											print("MSG: cliente %d inativo. Conexão encerrada" % dst_id)

									else:
										msg = generateERRO(src_id, seq_num)
										s.send(msg)
										print("MSG: destinatário não existe")
							else:
								generateERRO(src_id, seq_num)
								s.send(msg)
								print("MSG: ID de origem incorreto")


						elif msg_type == CREQ:

							# Check if source ID is correct
							if src_id == clients[s]:
								print("CREQ: lista de clientes solicidada por %d" % src_id)
								msg = generateCLIST(clients, src_id, seq_num)
								s.send(msg)

								try:
									data = s.recv(HEADER_SIZE)
									header = unpack('!HHHH', data) # 4 unsigned short = 8 bytes
									if header[0] == OK:
										print("CLIST: lista de clientes entregue a %d" % src_id)
								except socket.timeout:
									del clients[s]
									socket_list.remove(s)
									s.close()
									print("CREQ: cliente %d inativo. Conexão encerrada" % src_id)

							else:
								msg = generateERRO(src_id, seq_num)
								s.send(msg)
								print("CREQ: ID de origem incorreto")

						# Message type is not recognized
						else:
							msg = generateERRO(src_id, seq_num)
							s.send(msg)
							print("ERRO: tipo de mensagem incorreto")


				except socket.timeout:
					socket_list.remove(s)
					s.close()

	except Exception as e:
		print("Algo deu errado! ", e.__class__.__name__)
		server_socket.close()
		os._exit(1)

server_socket.close()