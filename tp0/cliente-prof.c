#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils.h"

int main(int argc, const char* argv[]){
	// execution parameter treatment
	if(argc==2){
		if(strlen(argv[1]) != 8){
			printf("Key must has 8 char\n");
			return -1;
		}
	} else {
		printf("ERROR: Execute without key param\n");
		return -1;
	}

	// initialing socket
	struct sockaddr_in serv_addr;
	int server_sck;

	if ((server_sck = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Socket creation error \n");
		return -1;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(PORT);

	if (connect(server_sck, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("TIMEOUT\n");
		return -1;
	}

	int len;
	len = MAX_CHAR_ON_INT;
	char buff[len+1];

	if(!recv_(server_sck, buff, READY_LENGTH, 0, "READY")) exit(EXIT_FAILURE);
	if(!send_(server_sck, argv[1], KEY_LENGTH, 0)) exit(EXIT_FAILURE);
	int i;
	while(1){
		memset(buff, '\0', (len+1)*sizeof(char));
		i = recv(server_sck, buff, len+1, 0);

		printf("%s", buff);
		if(i < 0) exit(EXIT_FAILURE);
		else if (i>0 && buff[i-1]=='\0') break;
	}

	if(!send_(server_sck, "OK", OK_LENGTH, 0)) exit(EXIT_FAILURE);
	close(server_sck);
	return 0;
}
