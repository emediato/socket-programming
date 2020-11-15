#include <pthread.h>
#include <stdio.h>

typedef struct thpoll{
    int qtt_threads;
    pthread_t *threads;
    int *available_threads;
    int qtt_available_threads;
} thpoll;

void begin_thread_proccess_(thpoll *poll){
    poll->available_threads = malloc(poll->qtt_threads*sizeof(int));
    poll->qtt_available_threads = poll->qtt_threads;
    for(int i=0; i<poll->qtt_threads; i++) poll->available_threads[i] = i;
}

int can_create_thread_(thpoll *poll){
    return poll->qtt_available_threads != 0;
}

//return index of poll to add a new thread
int get_new_thread_id(thpoll *poll){
    return poll->available_threads[poll->qtt_available_threads-1];
}

//call function thread and manipulate poll
int create_thread_(thpoll *poll, void *(*start_routine) (void *), void *arg){
    poll->qtt_available_threads--;
    int th = poll->available_threads[poll->qtt_available_threads];
    pthread_create(&(poll->threads[th]), NULL, start_routine, arg);
    return th;
}

// manipulate poll and stop thread execution
int close_thread_(thpoll *poll, int thread_id){
    poll->available_threads[poll->qtt_available_threads] = thread_id;
    poll->qtt_available_threads++;
    pthread_exit(EXIT_SUCCESS);
}

//free memory
void end_thread_proccess_(thpoll *poll){
    free(poll->available_threads);
}
