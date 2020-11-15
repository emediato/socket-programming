#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>

#define PORT 51511
#define STUDENT 1
#define PROFESSOR 2
#define KEY_LENGTH 8
#define MAX_STUDENTS 256

#define MAX_CHAR_ON_INT 10
#define READY_LENGTH 5
#define INTEGER_MAX_LENGTH 8
#define OK_LENGTH 2

int recv_(int sockfd, char buff[], int size, int flag, const char* expected_data){
	int i;
	//check timeout occurrence
	if( (i = recv(sockfd, buff, size, flag)) < 0 ||
		errno == EAGAIN || errno == EWOULDBLOCK
		|| errno == ETIMEDOUT){
		printf("TIMEOUT\n");
		return 0;
	}

	//check difference between received data and expected data
	if(expected_data != NULL &&
	strstr(buff, expected_data) != buff) {
		printf("TIMEOUT\n");
		return 0;
	}
	return 1;
}

int send_(int sockfd, const char buff[], int size, int flag){
	int i;
	//check timeout occurrence
	if( (i = send(sockfd, buff, size, flag)) < 0||
		errno == EAGAIN || errno == EWOULDBLOCK
		|| errno == ETIMEDOUT){
		printf("TIMEOUT\n");
		return 0;
	}
	return 1;
}
