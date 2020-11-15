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
	int num;
	//execution param treatment
	if(argc==5){
		if(strlen(argv[3]) != 8){
			printf("Key must has 8 char\n");
			return -1;
		}
		num = atoi(argv[4]);
	} else {
		printf("ERROR: Execute without key param\n");
		return -1;
	}

	//initializing server connection
	int server_sck;
	if(!(server_sck = begin_active_socket(argc, argv))){
		return -1;
	}

	char buff[11];
	const char *mat = "MATRICULA";
	const char *ok = "OK";

	if(!recv_(server_sck, buff, READY_LENGTH, 0, "READY")) exit(EXIT_FAILURE);
	if(!send_(server_sck, argv[3], KEY_LENGTH, 0)) exit(EXIT_FAILURE);
	if(!recv_(server_sck, buff, OK_LENGTH, 0, ok)) exit(EXIT_FAILURE);
	if(!recv_(server_sck, buff, strlen(mat), 0, mat)) exit(EXIT_FAILURE);

	//send number
	int32_t conv;
	conv = htonl(num);
	char *data;
	data = (char*)&conv;
	int len;
	len = sizeof(conv);

	if(!send_(server_sck, data, len, 0)) exit(EXIT_FAILURE);
	if(!recv_(server_sck, buff, OK_LENGTH, 0, ok)) exit(EXIT_FAILURE);

	close(server_sck);

	return 0;
}
