// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int i = 0;

pthread_mutex_t mut; 

// Note the return type: void*
void* incrementingThreadFunction(){
    
    for(int n = 0; n < 1000000;){
        pthread_mutex_lock(&mutex1);
        i++;
        n++;
        pthread_mutex_unlock(&mutex1);
    }
    
    return NULL;
    
}

void* decrementingThreadFunction(){
    
    for(int n = 0; n < 1000000;){
        pthread_mutex_lock(&mutex1);
        i--;
        n++;
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
    
}


int main(){
    // Using mutex as ther is only one shared resource
    if(pthread_mutex_init(&mut, NULL) != 0){
        printf("mutex init error");
        exit(0);
    }

    // TODO: 
    pthread_t t1, t2;
    char *message1 = "thread 1";
    char *message2 = "thread 2";
    int iret1, iret2;
    // start the two functions as their own threads using `pthread_create`
    // Hint: search the web! Maybe try "pthread_create example"?
    pthread_t thread1;
    pthread_t thread2;
    if(pthread_create(&thread1, NULL, incrementingThreadFunction, NULL) != 0){
        printf("Thread1 error");
        exit(0);
    }
    if(pthread_create(&thread2, NULL, decrementingThreadFunction, NULL) != 0){
        printf("Thread2 error");
        exit(0);
    }
    
    iret1 = pthread_create(&t1, NULL, incrementingThreadFunction, NULL);
    iret2 = pthread_create(&t2, NULL, decrementingThreadFunction, NULL);
    // TODO:
    // wait for the two threads to be done before printing the final result
    // Hint: Use `pthread_join`  
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);  
    printf("The magic number is: %d\n", i);
    return 0;
}
