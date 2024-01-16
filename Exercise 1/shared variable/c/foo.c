// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int i = 0;
pthread_mutex_t lock;

pthread_mutex_t mut; 

// Note the return type: void*
void* incrementingThreadFunction(){
    // TODO: increment i 1_000_000 times
    for(int x = 0; x < 1000000; x++){
        if(pthread_mutex_lock(&mut) != 0){
            printf("mutex lock error");
            exit(0);
        }
        i++;
        if(pthread_mutex_unlock(&mut) != 0){
            printf("mutex unlock error");
            exit(0);
        }
    }
    return NULL;
}

void* decrementingThreadFunction(){
    // TODO: decrement i 1_000_000 times
    
    
    for(int x = 0; x < 1000000-5; x++){
        if(pthread_mutex_lock(&mut) != 0){
            printf("mutex lock error");
            exit(0);
        }
        i--;
        if(pthread_mutex_unlock(&mut) != 0){
            printf("mutex unlock error");
            exit(0);
        }
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
    
    // TODO:
    // wait for the two threads to be done before printing the final result
    // Hint: Use `pthread_join` 

    if(pthread_join(thread1, NULL) != 0){
        printf("thread1 error");
        exit(0);
    }
    if(pthread_join(thread2, NULL) != 0){
        printf("thread2 error");
        exit(0);
    }
    
    
    printf("The magic number is: %d\n", i);
    return 0;
}
