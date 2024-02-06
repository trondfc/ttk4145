#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h> 
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

struct message
{
    long message_type;
    char message_text[100];
};

int main() {
    system("gnome-terminal -- ./counter");
    //return 0;

    struct msqid_ds buf;
    key_t key = ftok("keyfile", 65);
    /* create message queue */
    int msqid = msgget(key, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");

        exit(EXIT_FAILURE);
    }
    
    struct message message; 
    while (1)
    {
        
        msgrcv(msqid, &message, sizeof(message), 1, 0); 
        msgctl(msqid, IPC_STAT, &buf);
        printf("Received: %s\n", message.message_text);
        printf("msg time of last msgsnd: %ld\n", buf.msg_rtime);
    }
    
}

