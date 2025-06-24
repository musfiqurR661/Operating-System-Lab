#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mtx;

void* increment_counter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mtx);

        counter++;  // critical region

        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    pthread_t threads[3];
    pthread_mutex_init(&mtx, 0);
    
    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final counter: %d\n", counter);
    printf("Expected: 300000\n");
    
    return 0;
}

/*
counter = 5

P1 -> read 5, switch
P2 -> read 5, increment to 6
P1 -> (5) -> increment to 6
*/

// Compile: gcc -o counter counter.c -lpthread
// Run: ./counter