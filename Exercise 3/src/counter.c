#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h> 
#include <string.h>

struct message
{
    long message_type;
    char message_text[100];
};


void* crashAfterTimeout(void* arg){
    sleep(10);
    printf("Crashing\n");
    exit(1);
}

void* incrementingThreadFunction(){
    key_t key = ftok("keyfile", 65);
    /* create message queue */
    int msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");

        exit(EXIT_FAILURE);
    }

    struct message message;
    message.message_type = 1;
    memset(message.message_text, 0, sizeof(message.message_text));

    char str[8];
    int i = 0;
    while (1)
    {
        i++;
        printf("Incrementing: %d\n", i);

        sprintf(str, "%d", i);
        strcpy(message.message_text, str);

        /* send message to queue */
        if (msgsnd(msqid, &message, (sizeof(long) + sizeof(message.message_text)) + 1, 0) == -1) {
            perror("msgsnd");

            exit(EXIT_FAILURE);
        } else {
            printf("Sent: %s\n", message.message_text);
        }

        usleep(10000);
    }
}

int main(){
    pthread_t thread1;
    pthread_t thread2;

    if(pthread_create(&thread1, NULL, incrementingThreadFunction, NULL) != 0){
        printf("Thread1 error");
        exit(0);
    }
    if(pthread_create(&thread2, NULL, crashAfterTimeout, NULL) != 0){
        printf("Thread2 error");
        exit(0);
    }

    if(pthread_join(thread1, NULL) != 0){
        printf("Thread1 join error");
        exit(0);
    }
    if(pthread_join(thread2, NULL) != 0){
        printf("Thread2 join error");
        exit(0);
    }
    printf("Both threads are done\n"); // This line will never be printed
    return 0;
}