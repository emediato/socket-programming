from GVL import *
from socket import *
from  errno import *
import sys, getopt
import time
import ipaddress
from util import *

def main(argv):
	global clientnet
	clientnet =(ipaddress.ip_interface(str(argv[0])))

	addr_from_terminal = ''
	period_from_terminal = ''

	try:
		opts, args = getopt.getopt(argv, "haddr:period", ["aaddr=", "pperiod="])
	except getopt.GetoptError:
		print ("clientUDP.py -addr <ADDR> -period <PERIOD>")
		sys.exit(2)
	for opt, arg in opts:
		if opt == "-h":
			print ("clientUDP.py -addr <ADDR> -period <PERIOD>")
			sys.exit()
		elif opt in ("-a", "--aaddr"):
			addr_from_terminal = arg
		elif opt in ("-p", "--pperiod"):
			period_from_terminal = arg

	serverName = gethostname()
	#print(serverName)
	# same as UDP server
	clientSocket = socket(AF_INET, SOCK_DGRAM)

	s = ''


	while True:
		s = input('Insira os comandos add <ip> <weight> || del <ip> || trace <ip> || update || file <file.txt> :')

		s = s + ' ' + addr_from_terminal + ' ' + period_from_terminal

		sentence = s.encode('UTF-8')

		clientSocket.sendto(sentence, (serverName, SERVER_PORT))
		modifiedSentence, serverAddress = clientSocket.recvfrom(2048)
		# will receive at most buffer size of 2048 bytes
		print('Received from Router:', modifiedSentence.decode('UTF-8'))
		if s == 'stop':
			break

	clientSocket.close()


if __name__ == "__main__":
    main(sys.argv[1:]) # ip period
