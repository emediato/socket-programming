# imports

import socket
import select
import sys
import os
from struct import pack, unpack
import time

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

# Timeout
TIMEOUT = 5 # seconds

# Header size in bytes
HEADER_SIZE = 8


# Create an OK message to be sent
def generateOK(dst, seq):
	msg = pack('!HHHH', OK, SERVER_ID, dst, seq)
	return msg


# Creates an OI message to be sent
def generateOI(seq):
	msg = pack('!HHHH', OI, 0, SERVER_ID, seq)
	return msg


def main():

	if len(sys.argv) < 3:
		print('Erro. Número incorreto de parâmetros.')
		os._exit(1)

	HOST, PORT = sys.argv[1], int(sys.argv[2])
	BUFSZ = 500

	# Create an INET, STREAMING socket.
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# Connect the socket to he port where the server is listening
	sock.connect((HOST, PORT))
	sock.settimeout(TIMEOUT)

	my_id = 0
	seq_num = 0

	# Send OI message to server
	oi_msg = generateOI(seq_num)
	sock.send(oi_msg)

	# Waits for OK from server
	try:
		data = sock.recv(HEADER_SIZE)
		header = unpack('!4H', data)
		msg_type = header[0]

		if msg_type == OK:
			my_id = header[2]
			print("\nConexão estabelecida com servidor. O ID deste cliente é %d\n" % my_id)
		else:
			print("Servidor não confirmou a mensagem OI. Encerrando...")
			sock.close()
			os._exit(1)
	
	except socket.timeout:
		print("Temporizado. Encerrando...")
		sock.close()
		os._exit(1)


	print("::::::::::::::::::::::::::::::::::: MENU :::::::::::::::::::::::::::::::::::")
	print("-> Para enviar uma mensagem, digite MSG <id_destino> <texto>")
	print("-> Para ver a lista de clientes, digite CREQ")
	print("-> Para sair do sistema, digite FLW\n")

	while True:
		try:
			readable, writable, exceptional = select.select([0, sock], [], [])

			# For each socket readabled
			for s in readable:

				# 0 stands for stdin
				if s == 0:
					m = sys.stdin.readline().strip().split(' ')

					try:
						# In case user wants to send a message
						if m[0] == 'MSG':
							msg_type = MSG
							dst_id = int(m[1])
							del m[0]
							del m[0]
							msg = ' '.join(m)

							# Send message only if message has 400 or less characters
							if len(msg) <= 400:
								msg_size = len(msg.encode())
								header = pack('!HHHHH', msg_type, my_id, dst_id, seq_num, msg_size)
								sock.send(header)
								sock.send(msg.encode())

							# increase sequence number to next command
							seq_num += 1
						
						# In case user wants to see the list of active clients
						elif m[0] == 'CREQ':
							msg_type = CREQ
							dst_id = SERVER_ID
							data = pack('!HHHH', msg_type, my_id, dst_id, seq_num)
							sock.send(data)

							# increase sequence number to next command
							seq_num += 1

						# In case user wants to close the connection with server
						elif m[0] == 'FLW':
							msg_type = FLW
							dst_id = SERVER_ID
							data = pack('!HHHH', msg_type, my_id, dst_id, seq_num)
							sock.send(data)

							# Wait OK from server
							data = sock.recv(HEADER_SIZE)
							header = unpack('!HHHH', data)
							if header[0] == OK:
								print("Conexão encerrada com servidor.")
								sock.close()
								os._exit(1)

							# increase sequence number to next command
							seq_num += 1
						else:
							print("Comando incorreto.\n")

					# Catch timeout when client is waiting for OK
					except socket.timeout:
						print("")
					


				# Client receives data from socket
				elif s == sock:
					data = sock.recv(HEADER_SIZE)
					
					# Do something only if data is not empty
					if data != b'':
						header = unpack('!HHHH', data)
						msg_type = header[0]
						src_id = header[1]
						dst_id = header[2]
						seq_num = header[3]

						if msg_type == ERRO:
							print("ERRO!\n")
						
						elif msg_type == OK:
							print("Enviada!\n")

						# Receives message from server
						elif msg_type == MSG:
							# Receives size and text from message
							data = sock.recv(2)
							msg_size = unpack('!H', data)[0]
							data = sock.recv(msg_size + 1)
							msg_text = data.decode()
							
							# Send OK to server
							ok_msg = generateOK(src_id, seq_num)
							sock.send(ok_msg)

							print("Mensagem recebida de " + str(src_id) + ": " + msg_text + "\n")

						# Receives list of active clients
						elif msg_type == CLIST:
							data = sock.recv(2)
							num_clients = unpack('!H', data)[0]
							print("Lista de clientes ativos")
							data = sock.recv(num_clients * 2)
							clients = list(unpack('!%dH' % num_clients, data))

							# Print list of clients
							for client in clients:
								print("ID: %d" % client)
							print("\n")

							# Send OK to server
							ok_msg = generateOK(src_id, seq_num)
							sock.send(ok_msg)

		except Exception as e:
			print("Algo deu errado! ", e.__class__.__name__)
			sock.close()
			break

	# sock.close()

if __name__ == '__main__':
	main()
