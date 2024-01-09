// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int i = 0;
pthread_mutex_t lock;


// Note the return type: void*
void* incrementingThreadFunction(){
    // TODO: increment i 1_000_000 times
    
    
     for(u_int32_t counter = 0; counter < 1000002; counter++){
        if (pthread_mutex_lock(&lock) != 0){
            printf("Mutex lock failed on incrementingThreadFunction()");
            exit(0);
        }

        i++;

        if (pthread_mutex_unlock(&lock) != 0){
            printf("Mutex unlock failed on incrementingThreadFunction()");
            exit(1);
        }
    }
    
    
    return NULL;
}

void* decrementingThreadFunction(){
    // TODO: decrement i 1_000_000 times
    
    
     for(u_int32_t counter = 0; counter < 1000000; counter++){
        if (pthread_mutex_lock(&lock) != 0){
            printf("Mutex lock failed on decrementingThreadFunction()");
            exit(0);
        }

        i--;

        if (pthread_mutex_unlock(&lock) != 0){
            printf("Mutex unlock failed on decrementingThreadFunction()");
            exit(1);
        } 
    }
    

    return NULL;
}


int main(){
    // TODO: 
    // start the two functions as their own threads using `pthread_create`
    // Hint: search the web! Maybe try "pthread_create example"?
    pthread_t thread_1;
    pthread_t thread_2;
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("Creation of mutex failed");
        return 1;
    }

    if (pthread_create(&thread_1, NULL, incrementingThreadFunction, "thread_1") != 0){
        printf("pthread_create() error for thread_1");
    }

    if (pthread_create(&thread_2, NULL, decrementingThreadFunction, "thread_2") != 0){
        printf("pthread_create() error for thread 2");
    }

    // TODO:
    // wait for the two threads to be done before printing the final result
    // Hint: Use `pthread_join`    
    (void) pthread_join(thread_1, NULL);
    (void) pthread_join(thread_2, NULL);
    
    
    printf("The magic number is: %d\n", i);
    return 0;
}
