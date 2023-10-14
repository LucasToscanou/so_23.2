#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define NUM_THREADS 2

void *concorrencia(void *threadid) {
    int t = (int *)threadid;
    int segmento1, *vetor, size = 10000000;
    clock_t *time;

    segmento1 = shmget(7000, sizeof(int) * size, IPC_CREAT | S_IRUSR | S_IWUSR);

    // Attach shared memory segments
    vetor = (int *)shmat(segmento1, 0, 0);
    for(int i = 0; i < size; i++){
        vetor[i] *= 2;
        vetor[i] += 2;
    }
    
}

int main() {
    int segmento1, *vetor, size = 10000000, soma_total = 0;

    segmento1 = shmget(7000, sizeof(int) * size, IPC_CREAT | S_IRUSR | S_IWUSR);

    // Attach shared memory segments
    vetor = (int *)shmat(segmento1, 0, 0);

    pthread_t threads[NUM_THREADS];
    int t;

    for(int i = 0; i < size; i++)
      vetor[i] = 5;

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], NULL, concorrencia, (void *)t);
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    for(int i = 0; i < size; i++){
        if (vetor[i] != 26)
            printf("%d ",vetor[i]);
    }
    shmctl (segmento1, IPC_RMID, 0);
    return 0;
}





