#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h> 
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

typedef struct systemQueueData_t{
    long lastMsgType;
    char lastMsgText[100];
    long lastMsgNum;
    time_t lastMsgTime;
}systemQueueData_t;

typedef struct readSystemQueueArgs_t{
    systemQueueData_t* data;
    pthread_mutex_t* mutex;
}readSystemQueueArgs_t;


void* readSystemQueue(void* arg){
    readSystemQueueArgs_t* thread_args = (readSystemQueueArgs_t*)arg;
    systemQueueData_t* data = thread_args->data;
    pthread_mutex_t* systemQueueMutex = thread_args->mutex;

    struct message {  
    long message_type;
    char message_text[100];
    long message_num;
    }message;

    struct msqid_ds buf;    
    //struct message message; 
    key_t key = ftok("keyfile", 65);

    /* create message queue */
    int msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");

        exit(EXIT_FAILURE);
    }
    while(1){
        msgrcv(msqid, &message, sizeof(message), 1, 0); 
        msgctl(msqid, IPC_STAT, &buf);

        pthread_mutex_lock(systemQueueMutex);
        data->lastMsgType = message.message_type;
        strcpy(data->lastMsgText, message.message_text);
        data->lastMsgNum = message.message_num;
        data->lastMsgTime = buf.msg_rtime;
        pthread_mutex_unlock(systemQueueMutex);
    }
}


int main() {
    system("gnome-terminal -- ./counter");
    //return 0;

    systemQueueData_t* systemQueueData;
    systemQueueData = malloc(sizeof(systemQueueData_t));
    systemQueueData->lastMsgType = 0; 
    systemQueueData->lastMsgNum = 0;
    systemQueueData->lastMsgTime = 0;

    pthread_mutex_t systemQueueMutex;

    readSystemQueueArgs_t systemQueueDataArgs;
    systemQueueDataArgs.data = systemQueueData;
    systemQueueDataArgs.mutex = &systemQueueMutex;
    
    pthread_t systemQueueThread;

    if(pthread_mutex_init(&systemQueueMutex, NULL) != 0){
        printf("mutex init error");
        exit(0);
    }
    if(pthread_create(&systemQueueThread, NULL, readSystemQueue, &systemQueueDataArgs) != 0){
        printf("Thread1 error");
        exit(0);
    }

    time_t sys_time;
    while (1)
    {
        systemQueueData_t data;
        time(&sys_time);
        pthread_mutex_lock(&systemQueueMutex);
        data.lastMsgType = systemQueueData->lastMsgType;
        strcpy(data.lastMsgText, systemQueueData->lastMsgText);
        data.lastMsgNum = systemQueueData->lastMsgNum;
        data.lastMsgTime = systemQueueData->lastMsgTime;
        pthread_mutex_unlock(&systemQueueMutex);

        printf("Last message type: %ld\n", data.lastMsgType);
        printf("Last message text: %s\n", data.lastMsgText);
        printf("Last message number: %ld\n", data.lastMsgNum);
        printf("Last message time: %s\n", ctime(&data.lastMsgTime));
        printf("Current time: %s\n", ctime(&sys_time));
        if(data.lastMsgTime < sys_time - 2){
            printf("No message received in the last 2 seconds\n");
        }
        usleep(250000);

    }
    
}

