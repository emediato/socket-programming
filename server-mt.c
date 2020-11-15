
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include <pthread.h>

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "thread_treatment.h"

#define MAX_THREADS 5

int students[MAX_STUDENTS];
int n_students;
char professor_key[KEY_LENGTH+1] = {'\0'};
char student_key[KEY_LENGTH+1] = {'\0'};

thpoll poll;

// generate keys on ascii only alpha numeric characters
void get_keys(char *professor, char *student){
	srand(time(NULL));
	int i, r;
	for(i=0; i<KEY_LENGTH; i++){
		r = (rand()%75)+48;
		if((r>=58 && r<=64) || (r>=91 && r<=96)){
			i--;
		} else {
			professor[i] = r;
		}
	}

	for(i=0; i<KEY_LENGTH; i++){
		r = (rand()%75)+48;
		if((r>=58 && r<=64) || (r>=91 && r<=96)){
			i--;
		} else {
			student[i] = r;
		}
	}
}

//compare type of key
int type_of_key(char buffer[]){
	if(!(strncmp(buffer, professor_key, KEY_LENGTH)))
		return PROFESSOR;
	if(!(strncmp(buffer, student_key, KEY_LENGTH)))
		return STUDENT;
	else
		return -1;
}

int professor_proccess(int *students, int n, int client_sck){
	int len;
	len = MAX_CHAR_ON_INT;
	char buff[len+2];
	// for each student, aggegreate a string with the number + '\n'
	int i;
	for(i=0; i<n; i++){
		memset(buff, '\0', (len+2)*sizeof(char));
		sprintf(buff, "%d%c", students[i], '\n');
		if(!send_(client_sck, buff, strlen(buff), 0)) return 0;
	}

	if(!send_(client_sck, "\0", sizeof(char), 0)) return 0;
	if(!recv_(client_sck, buff, OK_LENGTH, MSG_WAITALL, "OK")) return 0;
	return 1;
}

int student_proccess(int client_sck, int students[], int *n_students){
	if(!send_(client_sck, "OK", OK_LENGTH, 0)) return 0;
	if(!send_(client_sck, "MATRICULA", strlen("MATRICULA"), 0)) return 0;

	if((*n_students) >= MAX_STUDENTS){
		printf("TIMEOUT");
		return 0;
	}
	// casting network data to integer
	int32_t ret;
	char *data = (char*)&ret;
	int left = sizeof(ret);

	int i;
	i = recv(client_sck, data, left, MSG_WAITALL);
	if(i<0 || i!=left) {
		printf("TIMEOUT\n");
		return 0;
	}

	if(!send_(client_sck, "OK", OK_LENGTH, 0)) return 0;
	students[*n_students] = ntohl(ret);
	(*n_students)++;
	return 1;
}

struct data {
	int th_id;
	int client_sck;
};

void *client_thread(void *param) {
    // pthread_t tid = pthread_self();
	// int *i = (int*)tid;
    struct data *dd = param;
	int id = dd->th_id;
	int client_sck = dd->client_sck;

    // set default timeout
	struct timeval tv;
	// set up timeout by 1 second
	tv.tv_sec = 1;
	tv.tv_usec = 0;
    setsockopt(client_sck, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
	setsockopt(client_sck, SOL_SOCKET, SO_SNDTIMEO,(struct timeval *)&tv,sizeof(struct timeval));

    char key[KEY_LENGTH];

    if(!send_(client_sck, "READY", READY_LENGTH, 0)){
        close(client_sck);
        errno = 0;
		free(dd);
		close_thread_(&poll, id);
    }

    //read key
    if(!recv_(client_sck, key, KEY_LENGTH, MSG_WAITALL, NULL)){
        close(client_sck);
        errno = 0;
		free(dd);
		close_thread_(&poll, id);
    }

    int type_key;
    type_key = type_of_key(key);

    if(type_key == STUDENT){
        //execute student proccess
        if(!student_proccess(client_sck, students, &n_students)){
            close(client_sck);
            errno = 0;
			free(dd);
			close_thread_(&poll, id);
        }
    } else if (type_key == PROFESSOR){
        //execute professor proccess
        if(!professor_proccess(students, n_students, client_sck)){
            errno = 0;
            close(client_sck);
			free(dd);
			close_thread_(&poll, id);
        }
    }
    close(client_sck);
	free(dd);
    close_thread_(&poll, id);
	void *a;
	return a;
}

int main(int argc, char const *argv[]){
	int server_sck, client_sck, len;
	struct sockaddr_in address;

	if(argc != 2){
		printf("ERROR: incorrect parameters number\n");
		return -1;
	}

	//getting initial keys
	get_keys(professor_key, student_key);
	printf("%s\n", professor_key);
	printf("%s\n", student_key);

	//initializing passive socket
	server_sck = begin_passive_socket(argc, argv);

	// threads poll
	pthread_t threads[MAX_THREADS];
	poll.qtt_threads = MAX_THREADS;
	poll.threads = threads;

	//initializing threads poll proccess
	begin_thread_proccess_(&poll);

	n_students = 0;
	len = sizeof(address);
	while(1){
		if((client_sck = accept(server_sck, (struct sockaddr*)&address, (socklen_t*)&len)) < 0){
			printf("TIMEOUT");
			continue;
		}

		//check wheter thread poll is not fully
		if(can_create_thread_(&poll)){
			//poll thread id
			int th_id = get_new_thread_id(&poll);
			//param passed by thread
			struct data *dt = malloc(sizeof(*dt));
			dt->client_sck = client_sck;
			dt->th_id = th_id;
			//execute communication using thread
			create_thread_(&poll, client_thread, dt);
		}
	}
	//free allocated memory
	end_thread_proccess_(&poll);
	return 0;
}
